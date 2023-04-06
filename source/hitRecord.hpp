#ifndef HITRECORD_HPP
#define HITRECORD_HPP

#include "common.hpp"

class Material;

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
#endif