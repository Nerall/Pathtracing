#pragma once

#include "Vector.hpp"
#include <limits>

class Ray
{
private:
    Vector origin;
    Vector direction;
    float t;
    float nearest;

public:
    Ray(Vector origin, Vector direction);
    Vector get_hit_point();
    float get_t_distance();
    void set_t_distance(float t);
    void set_nearest(float nearest);
    float get_nearest();
    Vector get_origin();
    Vector get_direction();
    ~Ray();
};


