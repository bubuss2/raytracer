#ifndef SURFACE_H
#define SURFACE_H

#include "hitRecord.h"
#include "ray.h"

class Surface
{
  public:
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
};

#endif