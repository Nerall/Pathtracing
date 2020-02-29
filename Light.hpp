#pragma once

#include "Vector.hpp"
#include <vector>

class Light
{
protected:
    Vector color;
    float intensity;

public:
    Light(Vector color, float intensity);
    Vector get_color();
    float get_intensity();
};


