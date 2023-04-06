#ifndef METAL_HPP
#define METAL_HPP

#include "common.hpp"
#include "material.hpp"

class Metal : public Material
{
  private:
    Color _albedo;

  public:
    Metal(const Color &albedo) : _albedo(albedo)
    {
    }

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override
    {
        Vector3 reflected = reflect(unit_vector(r_in.get_direction()), rec.normal);
        scattered = Ray(rec.p, reflected);
        attenuation = _albedo;
        return (dot(scattered.get_direction(), rec.normal) > 0);
    }
};

#endif