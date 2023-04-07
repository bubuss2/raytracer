#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <math.h>
#include <stdlib.h>

class Vector3
{
  private:
    float _values[3];

  public:
    __host__ __device__ Vector3()
    {
    }
    __host__ __device__ Vector3(float v0, float v1, float v2)
    {
        _values[0] = v0;
        _values[1] = v1;
        _values[2] = v2;
    }
    __host__ __device__ inline float x() const
    {
        return _values[0];
    }
    __host__ __device__ inline float y() const
    {
        return _values[1];
    }
    __host__ __device__ inline float z() const
    {
        return _values[2];
    }
    __host__ __device__ inline float r() const
    {
        return _values[0];
    }
    __host__ __device__ inline float g() const
    {
        return _values[1];
    }
    __host__ __device__ inline float b() const
    {
        return _values[2];
    }

    __host__ __device__ inline Vector3 operator-() const
    {
        return Vector3(-x(), -y(), -z());
    }

    __host__ __device__ inline float operator[](int i) const
    {
        return _values[i];
    }

    __host__ __device__ inline float &operator[](int i)
    {
        return _values[i];
    }

    __host__ __device__ inline float length() const
    {
        return std::sqrt(squared_sum());
    }
    __host__ __device__ inline float squared_sum() const
    {
        return std::pow(x(), 2) + std::pow(y(), 2) + std::pow(z(), 2);
    }

    __host__ __device__ inline Vector3 &operator+=(const Vector3 &v2);
    __host__ __device__ inline Vector3 &operator-=(const Vector3 &v2);
    __host__ __device__ inline Vector3 &operator*=(const Vector3 &v2);
    __host__ __device__ inline Vector3 &operator/=(const Vector3 &v2);
    __host__ __device__ inline Vector3 &operator*=(const float t);
    __host__ __device__ inline Vector3 &operator/=(const float t);
    __host__ __device__ inline void make_unit_vector();

    friend inline std::istream &operator>>(std::istream &is, Vector3 &v);
};

inline std::istream &operator>>(std::istream &is, Vector3 &v)
{
    is >> v._values[0] >> v._values[1] >> v._values[2];
    return is;
}

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v)
{
    out << v.x() << ' ' << v.y() << ' ' << v.z();
    return out;
}

__host__ __device__ inline void Vector3::make_unit_vector()
{
    float k = 1.0 / sqrt(x() * x() + y() * y() + z() * z());
    _values[0] *= k;
    _values[1] *= k;
    _values[2] *= k;
}

__host__ __device__ inline Vector3 operator+(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

__host__ __device__ inline Vector3 operator-(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

__host__ __device__ inline Vector3 operator*(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

__host__ __device__ inline Vector3 operator/(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.x() / v.x(), u.y() / v.y(), u.z() / v.z());
}

__host__ __device__ inline Vector3 operator*(float t, const Vector3 &v)
{
    return Vector3(t * v.x(), t * v.y(), t * v.z());
}

__host__ __device__ inline Vector3 operator/(Vector3 v, float t)
{
    return (1 / t) * v;
}

__host__ __device__ inline Vector3 operator*(const Vector3 &v, float t)
{
    return t * v;
}

__host__ __device__ inline float dot(const Vector3 &u, const Vector3 &v)
{
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

__host__ __device__ inline Vector3 cross(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(), u.x() * v.y() - u.y() * v.x());
}

__host__ __device__ inline Vector3 &Vector3::operator+=(const Vector3 &v)
{
    for (int i = 0; i < 3; i++)
    {
        _values[i] += v._values[i];
    }
    return *this;
}

__host__ __device__ inline Vector3 &Vector3::operator*=(const Vector3 &v)
{
    for (int i = 0; i < 3; i++)
    {
        _values[i] *= v._values[i];
    }
    return *this;
}

__host__ __device__ inline Vector3 &Vector3::operator/=(const Vector3 &v)
{
    for (int i = 0; i < 3; i++)
    {
        _values[i] /= v._values[i];
    }
    return *this;
}

__host__ __device__ inline Vector3 &Vector3::operator-=(const Vector3 &v)
{
    for (int i = 0; i < 3; i++)
    {
        _values[i] -= v._values[i];
    }
    return *this;
}

__host__ __device__ inline Vector3 &Vector3::operator*=(const float t)
{
    for (int i = 0; i < 3; i++)
    {
        _values[i] *= t;
    }
    return *this;
}

__host__ __device__ inline Vector3 &Vector3::operator/=(const float t)
{

    float k = 1.0 / t;
    for (int i = 0; i < 3; i++)
    {
        _values[i] *= k;
    }
    return *this;
}

__host__ __device__ inline Vector3 unit_vector(Vector3 v)
{
    return v / v.length();
}

typedef Vector3 Point;
typedef Vector3 Color;

#endif