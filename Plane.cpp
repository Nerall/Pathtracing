#include "Plane.hpp"

Plane::Plane(Vector point, Vector normal, float reflection_ratio): point(point), normal(normal)
{
    texture = Uniform_Texture(reflection_ratio);
}

bool Plane::collide(Ray &ray)
{
    auto denom = ray.get_direction().dot_product(normal);
    if (denom < 1e-8)
        return false;
    auto num = (point - ray.get_origin()).dot_product(normal);
    auto res = num / denom;
    if (res > 0)
    {
        ray.set_t_distance(num / denom);
        return true;
    }
    return false;
}

Vector Plane::get_normal(Vector &p)
{
    return normal.normalize();
}

float Plane::get_texture()
{
    texture.get_reflection_ratio();
}