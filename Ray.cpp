#include "Ray.hpp"

Ray::Ray(Vector origin, Vector direction) : origin(origin), direction(direction), hit(nullptr), t(0), nearest(std::numeric_limits<float>::max())
{}

std::shared_ptr<Object> Ray::get_hit()
{
    return hit;
}

void Ray::set_hit(std::shared_ptr<Object> object)
{
    hit = object;
}

Vector Ray::get_hit_point()
{
    return origin + t * direction;
}

float Ray::get_t_distance()
{
    return t;
}

void Ray::set_t_distance(float t)
{
    this->t = t;
}

void Ray::set_nearest(float nearest)
{
    this->nearest = nearest;
}

float Ray::get_nearest()
{
    return nearest;
}

Vector Ray::get_origin()
{
    return origin;
}

Vector Ray::get_direction()
{
    return direction;
}

Ray::~Ray(){}