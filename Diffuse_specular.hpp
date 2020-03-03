#pragma once

#include <iostream>
#include <vector>
#include "Texture_Material.hpp"
#include "Point_Light.hpp"
#include "Ray.hpp"

class Diffuse_specular: public Texture_Material
{
private:
    std::size_t exponent;
    float diffuse_weight;
    float specular_weight;
    float diffuse_ratio;

public:
    Diffuse_specular(std::size_t exponent, float diffuse_weight, float diffuse_ratio);
    float get_specular_weight();
    float get_diffuse_weight();
    std::size_t get_exponent();
    Vector get_reflection_direction(Ray &ray, Vector &hit_point, Point_Light &light);
    float get_diffuse_ratio();
    Vector get_color_light(Point_Light &light, Ray &ray, Vector &hit_point);
    ~Diffuse_specular();
};


