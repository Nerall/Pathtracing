#include "Sphere.hpp"

Sphere::Sphere(Vector center, float radius, float reflection_ratio): center(center), radius(radius)
{
    texture = Uniform_Texture(reflection_ratio);
}

bool Sphere::collide(Ray &ray)
{
    auto k = ray.get_origin() - center;
    float a = ray.get_direction().dot_product(ray.get_direction());
    float b = 2 * ray.get_direction().dot_product(k);
    float c = k.dot_product(k) - pow(radius, 2);
    auto discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant < 0)
        return false;
    else if (discriminant == 0)
        ray.set_t_distance(-b / (2 * a));
    else
    {
        auto x1 = (-b - sqrt(discriminant)) / (2 * a);
        auto x2 = (-b + sqrt(discriminant)) / (2 * a);
        if (x1 < 0 && x2 < 0)
            return false;
        else if (x1 > 0 && x2 > 0)
            ray.set_t_distance(std::min(x1, x2));
        else if (x1 < 0)
            ray.set_t_distance(x2);
        else
            ray.set_t_distance(x1);
    }
    return true;
}

Vector Sphere::get_normal(Vector &p)
{
    return (p - center).normalize();
}

float Sphere::get_texture()
{
    return texture.get_reflection_ratio();
}