#pragma once

#include "Texture_Material.hpp"

class Uniform_Texture: public Texture_Material
{
private:
    /* data */
public:
    Uniform_Texture();
    Uniform_Texture(float diffuse_ratio);
    float get_diffuse_ratio() override;
    ~Uniform_Texture();
};