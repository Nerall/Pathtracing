#include "Path_tracing_texture.hpp"

Path_tracing_texture::Path_tracing_texture(std::size_t exponent, float diffuse_weight, float diffuse_ratio): exponent(exponent), diffuse_weight(diffuse_weight), diffuse_ratio(diffuse_ratio)
{
    specular_weight = 1 - diffuse_weight;
}

Vector Path_tracing_texture::get_random_direction(float n1, float n2)
{
    float sinTheta = sqrtf(1 - powf(n1, 2)); 
    float phi = 2 * M_PI * n2; 
    float x = sinTheta * cosf(phi); 
    float z = sinTheta * sinf(phi); 
    return Vector(x, n1, z);
}

std::vector<Vector> Path_tracing_texture::create_transformation_matrix(Ray &ray, Vector &hit_point)
{
    Vector new_x;
    if (std::fabs(ray.get_hit()->get_normal(hit_point).get_x()) > std::fabs(ray.get_hit()->get_normal(hit_point).get_y()))
        new_x = Vector(ray.get_hit()->get_normal(hit_point).get_z(), 0, ray.get_hit()->get_normal(hit_point).get_x() * -1).normalize();
    else
        new_x = Vector(0, ray.get_hit()->get_normal(hit_point).get_z() * -1, ray.get_hit()->get_normal(hit_point).get_y()).normalize();
    Vector new_z = (ray.get_hit()->get_normal(hit_point).cross_product(new_x)).normalize();
    std::vector<Vector> transformation_matrix{new_x, ray.get_hit()->get_normal(hit_point), new_z};
    return transformation_matrix;
}

float Path_tracing_texture::get_specular_weight()
{
    return specular_weight;
}

float Path_tracing_texture::get_diffuse_weight()
{
    return diffuse_weight;
}

std::size_t Path_tracing_texture::get_exponent()
{
    return exponent;
}

float Path_tracing_texture::get_diffuse_ratio()
{
    return diffuse_ratio;
}

Vector Path_tracing_texture::get_color_light_brdf(Point_Light &light, Ray &ray, Vector &hit_point)
{
    Vector reflection_direction = get_reflection_direction(ray, hit_point, light);
    float brdf = ((powf(std::max(0.f, reflection_direction.dot_product(ray.get_direction() * -1)), exponent) * ((exponent + 2) / (2 * M_PI)) * specular_weight) + ((1 / M_PI) * diffuse_weight)) * diffuse_ratio;
    Vector total_light = brdf * light.get_illumination(ray, hit_point);
    return total_light;
}

Vector Path_tracing_texture::get_reflection_direction(Ray &ray, Vector &hit_point, Point_Light &light)
{
    return (light.get_direction(hit_point) - 2 * ray.get_hit()->get_normal(hit_point) * ray.get_hit()->get_normal(hit_point).dot_product(light.get_direction(hit_point))).normalize();
}

Path_tracing_texture::~Path_tracing_texture()
{
}