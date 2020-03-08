#pragma once

#include "Light.hpp"
#include "Ray.hpp"


class Point_Light: public Light
{
private:
    Vector location;

public:
    Point_Light(float intensity, Vector location);
    Vector get_direction(Vector &hit_point);
    float get_intensity();
    Vector illuminate(Ray &ray, Vector &hit_point);
    Vector get_illumination(Ray &ray, Vector &hit_point);
    Vector get_location();
};