#ifndef VECTOR3_HPP
#define VECTOR3_HPP

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

#endif