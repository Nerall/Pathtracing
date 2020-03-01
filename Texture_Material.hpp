#pragma once
#include "Vector.hpp"
class Texture_Material
{
protected:
    
public:
    Texture_Material();
    virtual float get_fresnel_ratio(Ray &ray, Vector &hit_point);
    virtual Vector get_reflection_direction(Ray &ray, Vector hit_point);
    virtual Vector get_refraction_direction(Ray &ray, Vector hit_point);
    virtual Ray create_refraction_ray(Ray &ray, Vector hit_point);
    virtual Ray create_reflection_ray(Ray &ray, Vector hit_point);
    virtual float get_diffuse_ratio();
    ~Texture_Material();
};