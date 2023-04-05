#ifndef SURFACEList_HPP
#define SURFACEList_HPP

#include "surface.hpp"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class SurfaceList : public Surface
{
  private:
    std::vector<shared_ptr<Surface>> objects;

  public:
    SurfaceList()
    {
    }
    SurfaceList(shared_ptr<Surface> object)
    {
        add(object);
    }

    void clear()
    {
        objects.clear();
    }

    void add(shared_ptr<Surface> object)
    {
        objects.push_back(object);
    }

    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
    {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto &object : objects)
        {
            if (object->hit(r, t_min, closest_so_far, temp_rec))
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