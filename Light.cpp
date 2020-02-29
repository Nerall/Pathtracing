#include "Light.hpp"

Light::Light(Vector color, float intensity): color(color), intensity(intensity)
{}

Vector Light::get_color()
{
    return color;
}

float Light::get_intensity()
{
    return intensity;
}