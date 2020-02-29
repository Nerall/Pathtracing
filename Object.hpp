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
        reflection
    };
    Object(Surface_type type);
    Surface_type get_surface_type();
    virtual bool collide(Ray &ray) = 0;
    virtual Vector get_normal(Vector &p) = 0;
    virtual float get_texture() = 0;
    
protected:
    Surface_type type;
};