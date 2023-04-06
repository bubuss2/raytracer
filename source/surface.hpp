#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "material.hpp"
#include "ray.hpp"

struct HitRecord
{
    Point p;
    Vector3 normal;
    std::shared_ptr<Material> material;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray &r, const Vector3 &outward_normal)
    {
        front_face = dot(r.get_direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Surface
{
  public:
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
};

#endif