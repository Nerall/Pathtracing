#include "Object.hpp"

Object::Object(Surface_type type, float diffuse_ratio, float refraction_index): type(type), diffuse_ratio(diffuse_ratio), refraction_index(refraction_index)
{}

Object::Surface_type Object::get_surface_type()
{
    return type;
}

float Object::get_diffuse_ratio()
{
    return diffuse_ratio;
}

float Object::get_refraction_index()
{
    return refraction_index;
}

void Object::set_refraction_index(float refraction_index)
{
    this->refraction_index = refraction_index;
}