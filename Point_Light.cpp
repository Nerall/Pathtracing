#include "Point_Light.hpp"

Point_Light::Point_Light(float intensity, Vector location): Light(intensity), location(location)
{
}

Vector Point_Light::get_direction(Vector const& hit_point)
{
    return (hit_point - location).normalize();
}

Vector Point_Light::illuminate(Ray const& ray, Vector const& hit_point)
{
    return std::max(0.f, ray.get_hit()->get_normal(hit_point).dot_product(get_direction(hit_point) * -1)) * get_illumination(ray, hit_point);
}

Vector Point_Light::get_illumination(Ray const& ray, Vector const& hit_point)
{
    return intensity * ray.get_hit()->get_color() / (4 * M_PI * get_direction(hit_point).norm());
}

Vector Point_Light::illuminateOrigin(Ray const& ray, Vector const& hit_point) 
{
    return std::max(0.f, ray.getOriginObject()->get_normal(hit_point).dot_product(get_direction(hit_point) * -1)) * get_illuminationOrigin(ray, hit_point);
}

Vector Point_Light::get_illuminationOrigin(Ray const& ray, Vector const& hit_point) 
{
    return intensity * ray.getOriginObject()->get_color() / (4 * M_PI * get_direction(hit_point).norm());
}

Vector Point_Light::get_location()
{
    return location;
}