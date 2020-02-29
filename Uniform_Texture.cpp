#include "Uniform_Texture.hpp"

Uniform_Texture::Uniform_Texture()
{}

Uniform_Texture::Uniform_Texture(float diffuse_ratio): Texture_Material(diffuse_ratio)
{}

float Uniform_Texture::get_diffuse_ratio()
{
    return diffuse_ratio;
}

Uniform_Texture::~Uniform_Texture(){}