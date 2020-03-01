#include "Reflected_texture.hpp"

Reflected_texture::Reflected_texture(/* args */)
{
}

Vector Reflected_texture::get_reflected_direction(Ray &ray, Vector &hit_point)
{
    return ray.get_direction() - 2 * ray.get_hit()->get_normal(hit_point) * ray.get_hit()->get_normal(hit_point).dot_product(ray.get_direction());
}

Reflected_texture::~Reflected_texture()
{
}