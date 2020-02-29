#include "Plane.hpp"

Plane::Plane(Surface_type type, float diffuse_ratio, float refraction_index, Vector point, Vector normal):Object(type, diffuse_ratio, refraction_index), point(point), normal(normal)
{
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
    return diffuse_ratio;
}