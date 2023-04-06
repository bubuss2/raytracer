#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "common.hpp"

class Camera
{
  private:
    Point _origin;
    Point _lower_left_corner;
    Vector3 _horizontal;
    Vector3 _vertical;

  public:
    Camera(Point viewSource, Point viewTarget, Vector3 viewUp, double field_of_view, double aspect_ratio)
    {
        auto theta = degrees_to_radians(field_of_view);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        auto w = unit_vector(viewSource - viewTarget);
        auto u = unit_vector(cross(viewUp, w));
        auto v = cross(w, u);

        _origin = viewSource;
        _horizontal = viewport_width * u;
        _vertical = viewport_height * v;
        _lower_left_corner = _origin - _horizontal / 2 - _vertical / 2 - w;
    }

    Ray get_ray(double s, double t) const
    {
        return Ray(_origin, _lower_left_corner + s * _horizontal + t * _vertical - _origin);
    }
};
#endif