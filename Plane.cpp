#include "Plane.hpp"

Plane::Plane(Surface_type type, float diffuse_ratio, Vector point, Vector normal): Object(type)
{
    material = std::make_shared<Diffuse_texture>(diffuse_ratio);
}

Plane::Plane(Surface_type type, float refraction_index, Vector point, Vector normal): Object(type)
{
    material = std::make_shared<Refracted_reflected_texture>(refraction_index);
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

std::shared_ptr<Texture_Material> Plane::get_texture()
{
    return material;
}