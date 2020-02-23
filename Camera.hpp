#pragma once

#include "Vector.hpp"
#include "Object.hpp"
#include <memory>

class Camera
{
private:
    Vector center;
    Vector height;
    float fov;

public:
    Camera(Vector center, float fov);
    Vector get_origin();
    float get_fov();
    
    ~Camera();
};


