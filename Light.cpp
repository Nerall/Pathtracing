#include "Light.hpp"

Light::Light(float intensity): intensity(intensity)
{}

float Light::get_intensity()
{
    return intensity;
}