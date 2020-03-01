#include "Object.hpp"

Object::Object(Surface_type type): type(type)
{}

Object::Surface_type Object::get_surface_type()
{
    return type;
}