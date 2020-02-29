#include "Camera.hpp"

Camera::Camera(Vector center, Vector object_location, Vector up_hint, float fov, float aspect_ratio): center(center)
{
    direction = (object_location - center).normalize();
    right = direction.cross_product(up_hint).normalize();
    up = right.cross_product(direction).normalize();
    h = tan(fov / 2);
    w = aspect_ratio;
}

Vector Camera::get_origin()
{
    return center;
}

Ray Camera::create_ray(float x, float y)
{
    return Ray(center, (direction + up * y * h + right * x * w).normalize());
}