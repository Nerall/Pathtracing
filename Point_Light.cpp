#include "Point_Light.hpp"

Point_Light::Point_Light(Vector location, std::vector<Vector> rays): Light(location, rays)
{
}

Point_Light::~Point_Light()
{
}