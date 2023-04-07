#ifndef RAY_HPP
#define RAY_HPP

#include "vector3.hpp"

class Ray
{
  private:
    Point _origin;
    Vector3 _direction;

  public:
    Ray()
    {
    }

    Ray(const Point &origin, const Vector3 &direction) : _origin(origin), _direction(direction)
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