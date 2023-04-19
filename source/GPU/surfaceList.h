#ifndef SURFACEList_H
#define SURFACEList_H

#include "surface.h"

class SurfaceList : public Surface
{
  private:
    Surface** _objects;
    int _objects_size;

  public:
    SurfaceList()
    {
    }
    SurfaceList(Surface** objects, int objects_size)
    {
        _objects = objects;
        _objects_size = objects_size;
    }

    __device__ bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
    {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (int i = 0; i < _objects_size; i++)
        {
            if (_objects[i]->hit(r, t_min, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif