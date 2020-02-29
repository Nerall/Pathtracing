#pragma once

#include "Vector.hpp"
#include "Uniform_Texture.hpp"

class Ray;

class Object
{
protected:

public:
    Object() = default;
    virtual bool collide(Ray &ray) = 0;
    virtual Vector get_normal(Vector &p) = 0;
    virtual float get_texture() = 0;
};