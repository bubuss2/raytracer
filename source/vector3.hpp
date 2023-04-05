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
        return Vector3(-_values[0], -_values[1], -_values[2]);
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
        return std::pow(_values[0], 2) + std::pow(_values[1], 2) + std::pow(_values[2], 2);
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector3 &v);
    friend Vector3 operator+(const Vector3 &u, const Vector3 &v);
    friend Vector3 operator-(const Vector3 &u, const Vector3 &v);
    friend Vector3 operator*(const Vector3 &u, const Vector3 &v);
    friend Vector3 operator*(double t, const Vector3 &v);
    friend Vector3 operator*(const Vector3 &v, double t);
    friend Vector3 operator/(Vector3 &v, double t);
    friend double dot(const Vector3 &u, const Vector3 &v);
    friend Vector3 cross(const Vector3 &u, const Vector3 &v);
};

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v)
{
    return out << v._values[0] << ' ' << v._values[1] << ' ' << v._values[2];
}

inline Vector3 operator+(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u._values[0] + v._values[0], u._values[1] + v._values[1], u._values[2] + v._values[2]);
}

inline Vector3 operator-(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u._values[0] - v._values[0], u._values[1] - v._values[1], u._values[2] - v._values[2]);
}

inline Vector3 operator*(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u._values[0] * v._values[0], u._values[1] * v._values[1], u._values[2] * v._values[2]);
}

inline Vector3 operator*(double t, const Vector3 &v)
{
    return Vector3(t * v._values[0], t * v._values[1], t * v._values[2]);
}

inline Vector3 operator*(const Vector3 &v, double t)
{
    return t * v;
}

inline Vector3 operator/(Vector3 &v, double t)
{
    return (1 / t) * v;
}

inline double dot(const Vector3 &u, const Vector3 &v)
{
    return u._values[0] * v._values[0] + u._values[1] * v._values[1] + u._values[2] * v._values[2];
}

inline Vector3 cross(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u._values[1] * v._values[2] - u._values[2] * v._values[1],
                   u._values[2] * v._values[0] - u._values[0] * v._values[2],
                   u._values[0] * v._values[1] - u._values[1] * v._values[0]);
}

inline Vector3 unit_vector(Vector3 v)
{
    return v / v.length();
}

#endif