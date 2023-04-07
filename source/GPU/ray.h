#ifndef RAY_H
#define RAY_H

#include "vector3.h"

class Ray
{
  private:
    Point _origin;
    Vector3 _direction;

  public:
    __device__ Ray()
    {
    }

    __device__ Ray(const Point &origin, const Vector3 &direction) : _origin(origin), _direction(direction)
    {
    }

    __device__ Vector3 origin() const
    {
        return _origin;
    }

    __device__ Vector3 direction() const
    {
        return _direction;
    }

    __device__ Vector3 point_at_parameter(float t) const
    {
        return _origin + t * _direction;
    }
};

#endif