#include "Sphere.hpp"

Sphere::Sphere(/* args */)
{
}

Sphere::~Sphere()
{
}

bool Sphere::collide(Ray const& ray, float t)
{
    float t0, t1;
    auto origin = ray.get_origin;
    auto direction = ray.get_direction;
    auto l = origin - center;
    auto a = direction.dot_product(direction);
    auto b = 2 * direction.dot_product(l);
    auto c = l.dot_product(l) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;
    else if (discriminant == 0)
        t = -b / (2 * a);
    else
    {
        t0 = -b - sqrt(discriminant) / 2 * a;
        t1 = -b + sqrt(discriminant) / 2 * a;
        t = (t1 < t0) ? t1 : t0;
    }
    return true;
}

Vector Sphere::get_normale(Vector const &v1, Vector const &v2)
{

}

Uniform_Texture Sphere::get_texture()
{

}