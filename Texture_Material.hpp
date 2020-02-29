#pragma once
#include "Vector.hpp"
class Texture_Material
{
protected:
    float diffuse_ratio;

public:
    Texture_Material();
    Texture_Material(float diffuse_ratio);
    virtual float get_diffuse_ratio() = 0;
    ~Texture_Material();
};