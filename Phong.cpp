#include "Phong.hpp"

Phong::Phong(std::size_t exponent, float diffuse_weight, float diffuse_ratio): exponent(exponent), diffuse_weight(diffuse_weight), diffuse_ratio(diffuse_ratio)
{
    specular_weight = 1 - diffuse_weight;
}

float Phong::get_specular_weight()
{
    return specular_weight;
}

float Phong::get_diffuse_weight()
{
    return diffuse_weight;
}

Vector Phong::get_color_light(Point_Light &light, Ray &ray, Vector &hit_point)
{
    Vector diffuse_component = (diffuse_ratio / M_PI) * light.illuminate(ray, hit_point);
    Vector reflection_direction = get_reflection_direction(ray, hit_point, light);
    Vector specular_component = powf(std::max(0.f, reflection_direction.dot_product(ray.get_direction() * -1)), exponent) * light.get_illumination(ray, hit_point);
    return diffuse_component * diffuse_weight + specular_component * specular_weight;
}



std::size_t Phong::get_exponent()
{
    return exponent;
}

float Phong::get_diffuse_ratio()
{
    return diffuse_ratio;
}

Vector Phong::get_reflection_direction(Ray &ray, Vector &hit_point, Point_Light &light)
{
    return (light.get_direction(hit_point) - 2 * ray.get_hit()->get_normal(hit_point) * ray.get_hit()->get_normal(hit_point).dot_product(light.get_direction(hit_point))).normalize();
}

Phong::~Phong()
{
}