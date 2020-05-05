#pragma once

#include "Light.hpp"

class Distant_light: public Light
{
private:
    Vector direction;

public:
    Distant_light();
    Distant_light(float intensity, Vector direction);
    Vector get_direction();
    Vector get_direction() const;
    float get_intensity();
    Vector get_illumination(Vector const& color);
    Vector get_illumination(Vector const& color) const;
    Vector illuminate(Ray const& ray, Vector const& hit_point);
    Vector illuminate(Ray const& ray, Vector const& hit_point) const;
    Vector illuminateOrigin(Ray const& ray, Vector const& hit_point);
    Vector illuminateOrigin(Ray const& ray, Vector const& hit_point) const;
};


