#include "Object.hpp"

Object::Object(Surface_type type, std::shared_ptr<Texture_Material> material): type(type), material(material)
{}

Object::Surface_type Object::get_surface_type()
{
    return type;
}