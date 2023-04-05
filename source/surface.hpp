#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"

struct HitRecord
{
    Vector3 p;
    Vector3 normal;
    double t;
};

class Surface
{
  public:
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
};

#endif