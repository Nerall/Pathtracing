#include "Ray.hpp"

Ray::Ray(Vector origin, Vector direction, Color color): origin(origin), direction(direction), color(color)
{
}

Vector Ray::get_origin()
{
    return origin;
}

Vector Ray::get_direction()
{
    return direction;
}

Ray::~Ray()
{
}