#pragma once

#include "Vector.hpp"
#include "Ray.hpp"

class Reflected_texture: public Texture_Material
{
private:
    /* data */
public:
    Reflected_texture(/* args */);
    Vector get_reflected_direction(Ray &ray, Vector &hit_point);
    ~Reflected_texture();
};


