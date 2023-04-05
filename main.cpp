#include "color.hpp"
#include "vector3.hpp"

#include <iostream>

int main()
{
    // Image
    const int image_width = 512;
    const int image_height = 512;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (std::size_t j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (std::size_t i = 0; i < image_width; ++i)
        {
            Vector3 pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}