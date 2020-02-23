#include "Object.hpp"

Object::Object(Vector color): color(color)
{}

Vector Object::get_color()
{
    return color;
}