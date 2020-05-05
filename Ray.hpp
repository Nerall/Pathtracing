#pragma once

#include "Vector.hpp"
#include "Object.hpp"
#include <memory>
#include <limits>
#include <optional>

class Ray
{
private:
    Vector origin;
    Vector direction;
    std::shared_ptr<Object> hit;
    float t;
    float nearest;
    std::shared_ptr<Object> originObject;

public:
    Ray();
    Ray(Vector origin, Vector direction);
    Ray(Vector origin, Vector direction, std::shared_ptr<Object> const& originObject);
    std::shared_ptr<Object> get_hit();
    std::shared_ptr<Object> get_hit() const;
    void set_hit(std::shared_ptr<Object> object);
    Vector get_hit_point();
    float get_t_distance();
    std::shared_ptr<Object> getOriginObject() const;
    void set_t_distance(float t);
    void set_nearest(float nearest);
    float get_nearest();
    Vector get_origin();
    Vector get_direction();
    Vector get_direction() const;
    ~Ray();
};


