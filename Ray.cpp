#include "Ray.hpp"

Ray::Ray(Vector origin, Vector direction): origin(origin), direction(direction), t(0), nearest(std::numeric_limits<float>::max())
{
}

Vector Ray::get_origin()
{
    return origin;
}

Vector Ray::get_hit_point()
{
    return origin + direction * t;
}

Vector Ray::get_direction()
{
    return direction;
}

float Ray::get_t_distance()
{
    return t;
}

float Ray::get_nearest()
{
    return nearest;
}

void Ray::set_t_distance(float t)
{
    this->t = t;
}

void Ray::set_nearest(float nearest)
{
    this->nearest = nearest;
}

Ray::~Ray()
{
}