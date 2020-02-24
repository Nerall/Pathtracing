#pragma once

#include "Object.hpp"
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
    Sphere(Vector color, Vector center, float radius);
    bool collide(Ray &ray) override;
};


