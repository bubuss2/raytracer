#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "surface.hpp"
#include "vector3.hpp"

class Sphere : public Surface
{
  private:
    Vector3 _center;
    double _radius;

  public:
    Sphere()
    {
    }

    Sphere(Vector3 cen, double r) : _center(cen), _radius(r){};

    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
    {
        Vector3 oc = r.get_origin() - _center;
        auto a = r.get_direction().squared_sum();
        auto half_b = dot(oc, r.get_direction());
        auto c = oc.squared_sum() - _radius * _radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0)
            return false;
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root)
        {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        Vector3 outward_normal = (rec.p - _center) / _radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    };
};

#endif