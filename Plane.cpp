#include "Plane.hpp"

Plane::Plane(Surface_type type, Vector point, Vector normal, std::shared_ptr<Diffuse_texture> texture, Vector color): Object(type, texture, color), point(point), normal(normal)
{
}

Plane::Plane(Surface_type type, Vector point, Vector normal, std::shared_ptr<Refracted_reflected_texture> texture, Vector color): Object(type, texture, color), point(point), normal(normal)
{
}

Plane::Plane(Surface_type type, Vector point, Vector normal, std::shared_ptr<Diffuse_specular> texture, Vector color): Object(type, texture, color), point(point), normal(normal)
{
}

Plane::Plane(Surface_type type, Vector point, Vector normal, std::shared_ptr<Path_tracing_texture> texture, Vector color): Object(type, texture, color), point(point), normal(normal)
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

std::shared_ptr<Texture_Material> Plane::get_texture()
{
    return material;
}