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
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        Vector3 direction;

        if (cannot_refract)
        {
            direction = reflect(unit_direction, rec.normal);
        }
        else
        {
            direction = refract(unit_direction, rec.normal, refraction_ratio);
        }

        scattered = Ray(rec.p, direction);
        return true;
    }
};

#endif