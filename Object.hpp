#pragma once

#include "Vector.hpp"
#include "Ray.hpp"
#include "Uniform_Texture.hpp"

class Object
{
protected:
    Vector color;

public:
    Object(Vector color);
    Vector get_color();
    virtual bool collide(Ray &ray) = 0;
};


