#include "camera.hpp"
#include "color.hpp"
#include "common.hpp"
#include "dielectric.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "surfaceList.hpp"

#include <iostream>

SurfaceList random_scene()
{
    SurfaceList world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = random_double();
            Point center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - Point(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point(0, 0.5, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.3, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point(4, 1.5, 0), 1.0, material3));

    return world;
}

Color ray_color(const Ray &r, const Surface &world, int depth)
{
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
    {
        return Color(0, 0, 0);
    }

    HitRecord rec;

    if (world.hit(r, 0.001, infinity, rec))
    {
        Ray scattered;
        Color attenuation;
        if (rec.material->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered, world, depth - 1);
        }

        return Color(0, 0, 0);
    }

    Vector3 unit_direction = unit_vector(r.get_direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 20;
    const int max_depth = 10;

    // World
    auto world = random_scene();

    // Camera
    Point viewSource(13, 2, 3);
    Point viewTarget(0, 0, 0);
    Vector3 viewUp(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;
    Camera camera(viewSource, viewTarget, viewUp, 20, aspect_ratio, aperture, dist_to_focus);

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            Color pixel_Color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                Ray r = camera.get_ray(u, v);
                pixel_Color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_Color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}