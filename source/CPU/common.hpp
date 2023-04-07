#ifndef COMMON_HPP
#define COMMON_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double random_double(double start = 0.0, double end = 1.0)
{
    static std::uniform_real_distribution<double> distribution(start, end);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double clamp(double x, double min, double max)
{
    if (x < min)
    {
        return min;
    }

    if (x > max)
    {
        return max;
    }

    return x;
}

// Common Headers

#include "ray.hpp"
#include "vector3.hpp"

#endif