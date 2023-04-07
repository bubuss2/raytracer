#ifndef METAL_HPP
#define METAL_HPP

#include "common.hpp"
#include "material.hpp"

class Metal : public Material
{
  private:
    Color _albedo;
    double _fuzz;

  public:
    Metal(const Color &albedo, double fuzz) : _albedo(albedo), _fuzz(fuzz < 1 ? fuzz : 1)
    {
    }

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override
    {
        Vector3 reflected = reflect(unit_vector(r_in.get_direction()), rec.normal);
        scattered = Ray(rec.p, reflected + _fuzz * Vector3::random_in_unit_sphere());
        attenuation = _albedo;
        return (dot(scattered.get_direction(), rec.normal) > 0);
    }
};

#endif