#include "Object.hpp"

Object::Object(Surface_type type, std::shared_ptr<Texture_Material> material, Vector &color): color(color), type(type), material(material)
{}

Vector Object::get_color()
{
    return color;
}

Object::Surface_type Object::get_surface_type()
{
    return type;
}