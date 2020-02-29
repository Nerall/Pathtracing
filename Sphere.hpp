#pragma once

#include "Object.hpp"
#include "Uniform_Texture.hpp"
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
    Sphere(Surface_type type, float diffuse_ratio, float refraction_index, Vector center, float radius);
    bool collide(Ray &ray) override;
    Vector get_normal(Vector &p) override;
    float get_texture() override;
};
