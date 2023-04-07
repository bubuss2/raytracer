#ifndef SURFACEList_HPP
#define SURFACEList_HPP

#include "surface.hpp"

#include <memory>
#include <vector>

class SurfaceList : public Surface
{
  private:
    std::vector<std::shared_ptr<Surface>> _objects;

  public:
    SurfaceList()
    {
    }
    SurfaceList(std::shared_ptr<Surface> object)
    {
        add(object);
    }

    void clear()
    {
        _objects.clear();
    }

    void add(std::shared_ptr<Surface> object)
    {
        _objects.push_back(object);
    }

    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
    {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto &object : _objects)
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