#include "Point_Light.hpp"

Point_Light::Point_Light(Vector color, float intensity, Vector location): Light(color, intensity), location(location)
{
}

Vector Point_Light::get_direction(Vector &hit_point)
{
    return (hit_point - location).normalize();
}

float Point_Light::get_intensity()
{
    return intensity;
}

Vector Point_Light::illuminate(Ray &ray, Vector &hit_point)
{
    return std::max(0.f, ray.get_hit()->get_normal(hit_point).dot_product(get_direction(hit_point) * -1)) * get_illumination(hit_point);
}

Vector Point_Light::get_illumination(Vector &hit_point)
{
    return intensity * color / (4 * M_PI * get_direction(hit_point).norm());
}

Vector Point_Light::get_location()
{
    return location;
}

Point_Light::~Point_Light()
{
}