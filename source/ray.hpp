#ifndef RAY_H
#define RAY_H

#include "common.hpp"

class Ray
{
  private:
    Point _origin;
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