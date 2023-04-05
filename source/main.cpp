#include "color.hpp"
#include "ray.hpp"
#include "vector3.hpp"

#include <iostream>

double hit_sphere(const Vector3 &center, double radius, const Ray &r)
{
    Vector3 oc = r.get_origin() - center;
    auto a = r.get_direction().squared_sum();
    auto half_b = dot(oc, r.get_direction());
    auto c = oc.squared_sum() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    return (discriminant < 0) ? -1.0 : (-half_b - sqrt(discriminant)) / a;
}

Vector3 ray_color(const Ray &r)
{
    auto t = hit_sphere(Vector3(0, 0, -1), 0.5, r);

    if (t > 0.0)
    {
        Vector3 N = unit_vector(r.at(t) - Vector3(0, 0, -1));
        return 0.5 * Vector3(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    Vector3 unit_direction = unit_vector(r.get_direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
}

int main()
{

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Vector3(0, 0, 0);
    auto horizontal = Vector3(viewport_width, 0, 0);
    auto vertical = Vector3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vector3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            Vector3 pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}