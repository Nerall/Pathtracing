#include "Plane.hpp"

Plane::Plane(Surface_type type, Vector point, Vector normal, float reflection_ratio):Object(type), point(point), normal(normal)
{
    texture = Uniform_Texture(reflection_ratio);
}

bool Plane::collide(Ray &ray)
{
    float denom = ray.get_direction().dot_product(normal);
    if (std::abs(denom) < 1e-8)
        return false;
    auto num = (point - ray.get_origin()).dot_product(normal);
    auto res = num / denom;
    if (res >= 1e-8)
    {
        ray.set_t_distance(res);
        return true;
    }
    return false;
}

Vector Plane::get_normal(Vector &p)
{
    return (normal - p + p).normalize();
}

float Plane::get_texture()
{
    return texture.get_reflection_ratio();
}