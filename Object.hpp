#pragma once

#include "Vector.hpp"
#include "Uniform_Texture.hpp"

class Ray;

class Object
{
public:
    enum class Surface_type
    {
        diffuse,
        reflection,
        refraction
    };
    Object(Surface_type type, float diffuse_ratio, float refraction_index);
    Surface_type get_surface_type();
    float get_diffuse_ratio();
    float get_refraction_index();
    void set_refraction_index(float refraction_index);
    virtual bool collide(Ray &ray) = 0;
    virtual Vector get_normal(Vector &p) = 0;
    virtual float get_texture() = 0;
    
protected:
    Surface_type type;
    float diffuse_ratio;
    float refraction_index;
};