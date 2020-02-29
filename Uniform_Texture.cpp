#include "Uniform_Texture.hpp"

Uniform_Texture::Uniform_Texture()
{}

Uniform_Texture::Uniform_Texture(float reflection_ratio): Texture_Material(reflection_ratio)
{}

float Uniform_Texture::get_reflection_ratio()
{
    return reflection_ratio;
}

Uniform_Texture::~Uniform_Texture(){}