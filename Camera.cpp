#include "Camera.hpp"

Camera::Camera(Vector center, float fov): center(center), fov(fov)
{}

Vector Camera::get_origin()
{
    return center;
}



float Camera::get_fov()
{
    return fov;
}

Camera::~Camera()
{
}