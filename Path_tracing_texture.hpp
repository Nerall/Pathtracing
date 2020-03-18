#pragma once

#include "Texture_Material.hpp"
#include "Point_Light.hpp"
#include <random>

class Path_tracing_texture: public Texture_Material
{
private:
    std::size_t exponent;
    float diffuse_weight;
    float specular_weight;
    float diffuse_ratio;

public:
    Path_tracing_texture(std::size_t exponent, float diffuse_weight, float diffuse_ratio);
    float get_specular_weight();
    float get_diffuse_weight();
    std::size_t get_exponent();
    float get_diffuse_ratio();
    Vector get_random_direction(float n1, float n2);
    std::vector<Vector> create_transformation_matrix(Ray &ray, Vector &hit_point);
    Vector get_color_light_brdf(Point_Light &light, Ray &ray, Vector &hit_point);
    Vector get_reflection_direction(Ray &ray, Vector &hit_point, Point_Light &light);
    ~Path_tracing_texture();
};


