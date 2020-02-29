#pragma once

#include "Vector.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include <memory>

class Camera
{
private:
    Vector center;
    Vector direction;
    Vector right;
    Vector up;
    float h;
    float w;
    float fov;

public:
    Camera(Vector center, Vector object_location, Vector up_hint, float fov, float aspect_ratio);
    Vector get_origin();
    Ray create_ray(float x, float y);

    ~Camera();
};


