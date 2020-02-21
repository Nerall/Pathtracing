#include "Camera.hpp"

Camera::Camera(Vector center, Vector direction, Vector height, float fov_x, float fov_y, float z_min): center(center), direction(direction), height(height), fov_x(fov_x), fov_y(fov_y), z_min(z_min)
{
}

Camera::~Camera()
{
}