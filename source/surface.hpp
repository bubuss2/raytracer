#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "hitRecord.hpp"
#include "material.hpp"
#include "ray.hpp"

class Surface
{
  public:
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
};

#endif