#pragma once

#include "Light.hpp"

class Point_Light: public Light
{
private:
    Vector location;

public:
    Point_Light(float intensity, Vector location);
    Vector get_direction(Vector const& hit_point);
    Vector illuminate(Ray const& ray, Vector const& hit_point);
    Vector get_illumination(Ray const& ray, Vector const& hit_point);
    Vector illuminateOrigin(Ray const& ray, Vector const& hit_point);
    Vector get_illuminationOrigin(Ray const& ray, Vector const& hit_point);
    Vector get_location();
};