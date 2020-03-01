#pragma once

#include "Ray.hpp"
#include <algorithm>

class Refracted_reflected_texture: public Texture_Material
{
private:
    float refraction_ratio;

public:
    Refracted_reflected_texture(float refraction_ratio);
    float get_fresnel_ratio(Ray &ray, Vector &hit_point);
    Vector get_refraction_direction(Ray &ray, Vector hit_point);
    Vector get_reflection_direction(Ray &ray, Vector hit_point);
    Ray create_refraction_ray(Ray &ray, Vector hit_point);
    Ray create_reflection_ray(Ray &ray, Vector hit_point);
    ~Refracted_reflected_texture();
};


