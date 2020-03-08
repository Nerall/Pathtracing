#pragma once

#include "Vector.hpp"
#include "Texture_Material.hpp"
#include <memory>

class Ray;

class Object
{
public:
    enum class Surface_type
    {
        diffuse,
        reflection,
        refraction,
        reflection_refraction,
        diffuse_specular,
        path_tracing_texture
    };
    Object(Surface_type type, std::shared_ptr<Texture_Material> material, Vector &color);
    Surface_type get_surface_type();
    Vector get_color();
    virtual bool collide(Ray &ray) = 0;
    virtual Vector get_normal(Vector &p) = 0;
    virtual std::shared_ptr<Texture_Material> get_texture() = 0;
    
protected:
    Vector color;
    Surface_type type;
    std::shared_ptr<Texture_Material> material;
};