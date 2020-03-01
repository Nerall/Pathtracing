#pragma once

#include "Texture_Material.hpp"

class Refracted_texture: public Texture_Material
{
private:
    float refraction_ratio;

public:
    Refracted_texture(float refraction_ratio);
    ~Refracted_texture();
};


