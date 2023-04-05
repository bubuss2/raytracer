#ifndef COLOR_H
#define COLOR_H

#include "vector3.hpp"

#include <iostream>

void write_color(std::ostream &out, Vector3 pixel_color)
{
    out << static_cast<int>(255.999 * pixel_color.x()) << ' ' << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif