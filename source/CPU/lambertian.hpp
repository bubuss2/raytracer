#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "common.hpp"
#include "material.hpp"

class Lambertian : public Material
{
  private:
    Color _albedo;

  public:
    Lambertian(const Color &albedo) : _albedo(albedo)
    {
    }

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
        {
            scatter_direction = rec.normal;
        }

        scattered = Ray(rec.p, scatter_direction);
        attenuation = _albedo;
        return true;
    }
};

#endif