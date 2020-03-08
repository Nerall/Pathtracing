#pragma once

#include "Vector.hpp"
#include <vector>

class Light
{
protected:
    float intensity;

public:
    Light(float intensity);
    float get_intensity();
};


