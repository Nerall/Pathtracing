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
    Uniform_Texture texture;

public:
    Sphere(Surface_type type, Vector center, float radius, float reflection_ratio = 0.18);
    bool collide(Ray &ray) override;
    Vector get_normal(Vector &p) override;
    float get_texture() override;
};
