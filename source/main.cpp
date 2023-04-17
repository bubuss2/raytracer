#include "CPU/render.cpp"

#include <fstream>
#include <iostream>

int validate_predicate_input(std::string message, auto predicate)
{
    int input = 0;
    while (!predicate(input))
    {
        std::cout << message << std::endl;
        std::cin >> input;
    }
    return input;
}

int main()
{
    const auto is_positive = [](int input) { return input > 0; };

    const int image_width = validate_predicate_input("Enter the image width:", is_positive);
    const int image_height = validate_predicate_input("Enter the image height:", is_positive);
    const int samples_per_pixel = validate_predicate_input("Enter the samples per pixel:", is_positive);
    const int max_ray_depth = validate_predicate_input("Enter the maximum ray depth:", is_positive);

    const double aspect_ratio = (double)image_width / image_height;

    std::cout << "Enter filename" << std::endl;
    std::string filename;
    std::cin >> filename;

    std::ofstream outFile;
    outFile.open(filename + ".ppm");
    render_image(outFile, image_width, image_height, aspect_ratio, samples_per_pixel, max_ray_depth);
    outFile.close();

    return 0;
}