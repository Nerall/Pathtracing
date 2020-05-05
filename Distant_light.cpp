#include "Distant_light.hpp"

Distant_light::Distant_light(): Light(0), direction(0)
{}

Distant_light::Distant_light(float intensity, Vector direction): Light(intensity), direction(direction.normalize())
{}

Vector Distant_light::get_direction() 
{
    return direction.normalize();
}

Vector Distant_light::get_direction() const
{
    return direction.normalize();
}

Vector Distant_light::get_illumination(Vector const& color)
{
    return intensity * color;
}

Vector Distant_light::get_illumination(Vector const& color) const
{
    return intensity * color;
}

Vector Distant_light::illuminate(Ray const& ray, Vector const& hit_point)
{
    return std::max(0.f, ray.get_hit()->get_normal(hit_point).dot_product(get_direction() * -1)) * get_illumination(ray.get_hit()->get_color());
}

Vector Distant_light::illuminateOrigin(Ray const& ray, Vector const& hit_point) 
{
    return std::max(0.f, ray.getOriginObject()->get_normal(hit_point).dot_product(get_direction() * -1)) * get_illumination(ray.getOriginObject()->get_color());
}

Vector Distant_light::illuminateOrigin(Ray const& ray, Vector const& hit_point) const
{
    return std::max(0.f, ray.getOriginObject()->get_normal(hit_point).dot_product(get_direction() * -1)) * get_illumination(ray.getOriginObject()->get_color());
}

Vector Distant_light::illuminate(Ray const& ray, Vector const& hit_point) const
{
    return std::max(0.f, ray.get_hit()->get_normal(hit_point).dot_product(get_direction() * -1)) * get_illumination(ray.get_hit()->get_color());
}
