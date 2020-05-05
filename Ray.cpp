#include "Ray.hpp"

Ray::Ray(): origin(0), direction(0), hit(nullptr), t(0), nearest(std::numeric_limits<float>::max()), originObject(nullptr)
{
}

Ray::Ray(Vector origin, Vector direction) : origin(origin), direction(direction), hit(nullptr), t(0), nearest(std::numeric_limits<float>::max()), originObject(nullptr)
{
}

Ray::Ray(Vector origin, Vector direction, std::shared_ptr<Object> const& originObject) : origin(origin), direction(direction), hit(nullptr), t(0), nearest(std::numeric_limits<float>::max()), originObject(originObject)
{
}

std::shared_ptr<Object> Ray::get_hit()
{
    return hit;
}

std::shared_ptr<Object> Ray::get_hit() const
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

std::shared_ptr<Object> Ray::getOriginObject() const
{
    return originObject;
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
    return direction.normalize();
}

Vector Ray::get_direction() const
{
    return direction.normalize();
}

Ray::~Ray(){}