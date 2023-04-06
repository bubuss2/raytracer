#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "common.hpp"
#include <cmath>
#include <iostream>

class Vector3
{
  private:
    double _values[3];

  public:
    Vector3() : _values{0, 0, 0}
    {
    }

    Vector3(double v0, double v1, double v2) : _values{v0, v1, v2}
    {
    }

    double x() const
    {
        return _values[0];
    }

    double y() const
    {
        return _values[1];
    }

    double z() const
    {
        return _values[2];
    }

    Vector3 operator-() const
    {
        return Vector3(-x(), -y(), -z());
    }

    double operator[](int i) const
    {
        return _values[i];
    }

    double &operator[](int i)
    {
        return _values[i];
    }

    Vector3 &operator+=(const Vector3 &v)
    {
        for (int i = 0; i < 3; i++)
        {
            _values[i] += v._values[i];
        }
        return *this;
    }

    Vector3 &operator*=(const double v)
    {
        for (int i = 0; i < 3; i++)
        {
            _values[i] *= v;
        }
        return *this;
    }

    Vector3 &operator/=(const double v)
    {
        return *this *= (1 / v);
    }

    double length() const
    {
        return std::sqrt(squared_sum());
    }

    double squared_sum() const
    {
        return std::pow(x(), 2) + std::pow(y(), 2) + std::pow(z(), 2);
    }

    bool near_zero() const
    {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (fabs(x()) < s) && (fabs(y()) < s) && (fabs(z()) < s);
    }

    inline static Vector3 random()
    {
        return Vector3(random_double(), random_double(), random_double());
    }

    inline static Vector3 random(double min, double max)
    {
        return Vector3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    inline static Vector3 random_in_unit_sphere()
    {
        auto p = Vector3(infinity, infinity, infinity);
        while (p.squared_sum() >= 1)
        {
            p = Vector3::random(-1, 1);
        }
        return p;
    }
};

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v)
{
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline Vector3 operator+(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vector3 operator-(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vector3 operator*(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vector3 operator*(double t, const Vector3 &v)
{
    return Vector3(t * v.x(), t * v.y(), t * v.z());
}

inline Vector3 operator*(const Vector3 &v, double t)
{
    return t * v;
}

inline Vector3 operator/(Vector3 v, double t)
{
    return (1 / t) * v;
}

inline double dot(const Vector3 &u, const Vector3 &v)
{
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline Vector3 cross(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(), u.x() * v.y() - u.y() * v.x());
}

inline Vector3 unit_vector(Vector3 v)
{
    return v / v.length();
}

inline Vector3 random_unit_vector()
{
    return unit_vector(Vector3::random_in_unit_sphere());
}

inline Vector3 reflect(const Vector3 &v, const Vector3 &n)
{
    return v - 2 * dot(v, n) * n;
}

inline Vector3 refract(const Vector3 &uv, const Vector3 &n, double etai_over_etat)
{
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vector3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vector3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.squared_sum())) * n;
    return r_out_perp + r_out_parallel;
}

// Typedefs

typedef Vector3 Color;
typedef Vector3 Point;

#endif