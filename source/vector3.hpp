#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>
#include <iostream>

class Vector3
{
  private:
    double values[3]{};

  public:
    Vector3() : values{}
    {
    }

    Vector3(double v0, double v1, double v2) : values{v0, v1, v2}
    {
    }

    Vector3(const Vector3 &v)
    {
        std::copy(v.values, v.values + 2, values);
    }

    double x() const
    {
        return values[0];
    }

    double y() const
    {
        return values[1];
    }

    double z() const
    {
        return values[2];
    }

    Vector3 operator-() const
    {
        return Vector3(-values[0], -values[1], -values[2]);
    }

    Vector3 operator-(const Vector3 &v)
    {
        return *this + -v;
    }

    double operator[](std::size_t i) const
    {
        return values[i];
    }

    double &operator[](std::size_t i)
    {
        return values[i];
    }

    Vector3 &operator+=(const Vector3 &v)
    {
        for (std::size_t i = 0; i < 3; i++)
        {
            values[i] += v.values[i];
        }
        return *this;
    }

    Vector3 &operator*=(const double v)
    {
        for (std::size_t i = 0; i < 3; i++)
        {
            values[i] *= v;
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
        return std::pow(values[0], 2) + std::pow(values[1], 2) + std::pow(values[2], 2);
    }

    Vector3 unit_vector() const
    {
        auto length = this->length();
        return Vector3(values[0] / length, values[1] / length, values[2] / length);
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector3 &v);
    friend double dot(const Vector3 &v0, const Vector3 &v1);
    friend Vector3 cross(const Vector3 &v0, const Vector3 &v1);
    friend Vector3 operator*(double t, const Vector3 &v);
    friend Vector3 operator*(const Vector3 &v, double t);
    friend Vector3 operator/(Vector3 v, double t);
    friend Vector3 operator+(const Vector3 &v0, const Vector3 &v1);
    friend Vector3 operator-(const Vector3 &v0, const Vector3 &v1);
};

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v)
{
    return out << v.values[0] << ' ' << v.values[1] << ' ' << v.values[2];
}

inline double dot(const Vector3 &v0, const Vector3 &v1)
{
    return v0.values[0] * v1.values[0] + v0.values[1] * v1.values[1] + v0.values[2] * v1.values[2];
}

inline Vector3 cross(const Vector3 &v0, const Vector3 &v1)
{
    return Vector3(v0.values[1] * v1.values[2] - v0.values[2] * v1.values[1],
                   v0.values[2] * v1.values[0] - v0.values[0] * v1.values[2],
                   v0.values[0] * v1.values[1] - v0.values[1] * v1.values[0]);
}

inline Vector3 operator+(const Vector3 &v0, const Vector3 &v1)
{
    return Vector3(v0.values[0] + v1.values[0], v0.values[1] + v1.values[1], v0.values[2] + v1.values[2]);
}

inline Vector3 operator-(const Vector3 &v0, const Vector3 &v1)
{
    return Vector3(v0.values[0] - v1.values[0], v0.values[1] - v1.values[1], v0.values[2] - v1.values[2]);
}

inline Vector3 operator*(double t, const Vector3 &v)
{
    return Vector3(t * v.values[0], t * v.values[1], t * v.values[2]);
}

inline Vector3 operator*(const Vector3 &v, double t)
{
    return t * v;
}

inline Vector3 operator/(Vector3 v, double t)
{
    return (1 / t) * v;
}

#endif