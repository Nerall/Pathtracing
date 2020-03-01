#include "Diffuse_texture.hpp"

Diffuse_texture::Diffuse_texture()
{}

Diffuse_texture::Diffuse_texture(float diffuse_ratio): diffuse_ratio(diffuse_ratio)
{}

float Diffuse_texture::get_diffuse_ratio()
{
    return diffuse_ratio;
}

Diffuse_texture::~Diffuse_texture(){}