#pragma once

#include "Object.hpp"
#include "Diffuse_texture.hpp"
#include "Diffuse_specular.hpp"
#include "Path_tracing_texture.hpp"
#include "Refracted_reflected_texture.hpp"
#include "Ray.hpp"
#include "Vector.hpp"
#include <cmath>
#include <iostream>

class Sphere: public Object
{
private:
    Vector center;
    float radius;

public:
    Sphere(Surface_type type, std::shared_ptr<Diffuse_texture> texture, Vector center, float radius, Vector color);
    Sphere(Surface_type type, std::shared_ptr<Refracted_reflected_texture> texture, Vector center, float radius, Vector color);
    Sphere(Surface_type type, std::shared_ptr<Diffuse_specular> texture, Vector center, float radius, Vector color);
    Sphere(Surface_type type, std::shared_ptr<Path_tracing_texture> texture, Vector center, float radius, Vector color);
    bool collide(Ray &ray) override;
    Vector get_normal(Vector &p) override;
    std::shared_ptr<Texture_Material> get_texture() override;
};
