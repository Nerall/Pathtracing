#pragma once

#include "Vector.hpp"
#include <vector>
#include "Ray.hpp"

class Light
{
protected:
    float intensity;

public:
    Light(float intensity);
    virtual Vector illuminate(Ray const& ray, Vector const& hit_point) = 0;
};


