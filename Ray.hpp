#pragma once

#include "Vector.hpp"
#include "Object.hpp"
#include <memory>
#include <limits>

class Ray
{
private:
    Vector origin;
    Vector direction;
    std::shared_ptr<Object> hit;
    float t;
    float nearest;

public:
    Ray(Vector origin, Vector direction);
    std::shared_ptr<Object> get_hit();
    void set_hit(std::shared_ptr<Object> object);
    Vector get_hit_point();
    float get_t_distance();
    void set_t_distance(float t);
    void set_nearest(float nearest);
    float get_nearest();
    Vector get_origin();
    Vector get_direction();
    ~Ray();
};


