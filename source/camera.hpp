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
    Vector3 _u, _v, _w;
    double _lens_radius;

  public:
    Camera(Point viewSource, Point viewTarget, Vector3 viewUp, double field_of_view, double aspect_ratio,
           double aperture, double focus_distance)
    {
        auto theta = degrees_to_radians(field_of_view);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        _w = unit_vector(viewSource - viewTarget);
        _u = unit_vector(cross(viewUp, _w));
        _v = cross(_w, _u);

        _origin = viewSource;
        _horizontal = focus_distance * viewport_width * _u;
        _vertical = focus_distance * viewport_height * _v;
        _lower_left_corner = viewSource - _horizontal / 2 - _vertical / 2 - focus_distance * _w;

        _lens_radius = aperture / 2;
    }

    Ray get_ray(double s, double t) const
    {
        Vector3 rd = _lens_radius * random_in_unit_disk();
        Vector3 offset = _u * rd.x() + _v * rd.y();

        return Ray(_origin + offset, _lower_left_corner + s * _horizontal + t * _vertical - _origin - offset);
    }
};
#endif