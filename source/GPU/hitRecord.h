#ifndef HITRECORD_H
#define HITRECORD_H

#include "common.h"

struct HitRecord
{
    Point p;
    Vector3 normal;
    double t;

    __device__ void set_face_normal(const Ray &r, const Vector3 &outward_normal)
    {
        front_face = dot(r.get_direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

#endif