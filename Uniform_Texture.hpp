#pragma once

#include "Texture_Material.hpp"

class Uniform_Texture: public Texture_Material
{
private:
    /* data */
public:
    Uniform_Texture();
    Uniform_Texture(float reflection_ratio);
    float get_reflection_ratio() override;
    ~Uniform_Texture();
};