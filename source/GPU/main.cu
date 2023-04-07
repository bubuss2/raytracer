#include <iostream>
#include <time.h>

#include "ray.h"
#include "vector3.h"

// limited version of checkCudaErrors from helper_cuda.h in CUDA examples
#define checkCudaErrors(val) check_cuda((val), #val, __FILE__, __LINE__)

void check_cuda(cudaError_t result, char const *const func, const char *const file, int const line)
{
    if (result)
    {
        std::cerr << "CUDA error = " << static_cast<unsigned int>(result) << " at " << file << ":" << line << " '"
                  << func << "' \n";
        // Make sure we call CUDA Device Reset before exiting
        cudaDeviceReset();
        exit(99);
    }
}

__device__ bool hit_sphere(const Vector3 &center, float radius, const Ray &r)
{
    Vector3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0f * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4.0f * a * c;
    return (discriminant > 0.0f);
}

__device__ Vector3 get_color(const Ray &r)
{
    if (hit_sphere(Vector3(0, 0, -1), 0.5, r))
    {
        return Vector3(1, 0, 0);
    }

    Vector3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
}

__global__ void render(Vector3 *fb, int max_x, int max_y, Vector3 lower_left_corner, Vector3 horizontal,
                       Vector3 vertical, Vector3 origin)
{
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.y + blockIdx.y * blockDim.y;
    if ((i >= max_x) || (j >= max_y))
    {
        return;
    }

    int pixel_index = j * max_x + i;
    float u = float(i) / float(max_x);
    float v = float(j) / float(max_y);
    Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
    fb[pixel_index] = get_color(r);
}

int main()
{
    int nx = 1200;
    int ny = 600;
    int tx = 8;
    int ty = 8;

    std::cerr << "Rendering a " << nx << "x" << ny << " image ";
    std::cerr << "in " << tx << "x" << ty << " blocks.\n";

    int num_pixels = nx * ny;
    size_t fb_size = num_pixels * sizeof(Vector3);

    // allocate FB
    Vector3 *fb;
    checkCudaErrors(cudaMallocManaged((void **)&fb, fb_size));

    clock_t start, stop;
    start = clock();
    // Render our buffer
    dim3 blocks(nx / tx + 1, ny / ty + 1);
    dim3 threads(tx, ty);
    render<<<blocks, threads>>>(fb, nx, ny, Vector3(-2.0, -1.0, -1.0), Vector3(4.0, 0.0, 0.0), Vector3(0.0, 2.0, 0.0),
                                Vector3(0.0, 0.0, 0.0));
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaDeviceSynchronize());
    stop = clock();
    double timer_seconds = ((double)(stop - start)) / CLOCKS_PER_SEC;
    std::cerr << "took " << timer_seconds << " seconds.\n";

    // Output FB as Image
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            size_t pixel_index = j * nx + i;
            int ir = int(255.99 * fb[pixel_index].r());
            int ig = int(255.99 * fb[pixel_index].g());
            int ib = int(255.99 * fb[pixel_index].b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    checkCudaErrors(cudaFree(fb));
}