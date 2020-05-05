#pragma once

#include <iostream>
#include <vector>
#include "Texture_Material.hpp"
#include "Point_Light.hpp"
#include "Distant_light.hpp"
#include "Ray.hpp"

class Phong: public Texture_Material
{
private:
    std::size_t exponent;
    float diffuse_weight;
    float specular_weight;
    float diffuse_ratio;

public:
    Phong(std::size_t exponent, float diffuse_weight, float diffuse_ratio);
    float get_specular_weight();
    float get_diffuse_weight();
    std::size_t get_exponent();
    Vector get_reflection_direction(Ray &ray, Vector &hit_point, Point_Light &light);
    Vector get_reflection_direction(Ray const& ray, Vector const& hit_point, Distant_light const& light);

    float get_diffuse_ratio();
    Vector get_color_light(Point_Light &light, Ray &ray, Vector &hit_point);
    Vector get_color_light(Distant_light const& light, Ray const& ray, Vector const& hit_point);

    Vector get_color_light_brdf(Point_Light &light, Ray &ray, Vector &hit_point);
    ~Phong();
};


