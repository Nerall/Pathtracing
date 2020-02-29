#pragma once
#include "Vector.hpp"
class Texture_Material
{
protected:
    float reflection_ratio;

public:
    Texture_Material();
    Texture_Material(float reflection_ratio);
    virtual float get_reflection_ratio() = 0;
    ~Texture_Material();
};