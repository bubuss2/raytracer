#ifndef RAY_H
#define RAY_H

#include "vector3.hpp"

class Ray
{
  private:
    Vector3 _origin;
    Vector3 _direction;

  public:
    Ray()
    {
    }

    Ray(const Vector3 &origin, const Vector3 &direction) : _origin(origin), _direction(direction)
    {
    }

    Vector3 get_origin() const
    {
        return _origin;
    }

    Vector3 get_direction() const
    {
        return _direction;
    }

    Vector3 at(double t) const
    {
        return _origin + t * _direction;
    }
};

#endif