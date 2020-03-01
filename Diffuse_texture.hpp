#pragma once

#include "Texture_Material.hpp"

class Diffuse_texture: public Texture_Material
{
private:
    float diffuse_ratio;
public:
    Diffuse_texture();
    Diffuse_texture(float diffuse_ratio);
    float get_diffuse_ratio();
    ~Diffuse_texture();
};