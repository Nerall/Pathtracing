#pragma once

#include "Object.hpp"
#include "Diffuse_texture.hpp"
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
    Sphere(Surface_type type, float diffuse_ratio, Vector center, float radius);
    Sphere(Surface_type type, float refraction_index, Vector center, float radius);
    bool collide(Ray &ray) override;
    Vector get_normal(Vector &p) override;
    std::shared_ptr<Texture_Material> get_texture() override;
};
