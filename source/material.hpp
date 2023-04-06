#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "common.hpp"

class HitRecord;

class Material
{
  public:
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const = 0;
};

#endif