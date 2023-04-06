#ifndef DIELECTRIC_HPP
#define DIELECTRIC_HPP

#include "common.hpp"
#include "material.hpp"

class Dielectric : public Material
{
  private:
    double _refraction_index;

  public:
    Dielectric(double refraction_index) : _refraction_index(refraction_index)
    {
    }

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override
    {
        attenuation = Color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0 / _refraction_index) : _refraction_index;

        Vector3 unit_direction = unit_vector(r_in.get_direction());
        Vector3 refracted = refract(unit_direction, rec.normal, refraction_ratio);

        scattered = Ray(rec.p, refracted);
        return true;
    }
};

#endif