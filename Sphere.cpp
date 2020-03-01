#include "Sphere.hpp"

Sphere::Sphere(Surface_type type, float diffuse_ratio, Vector center, float radius): Object(type), center(center), radius(radius)
{
    material = std::make_shared<Diffuse_texture>(diffuse_ratio);
}

Sphere::Sphere(Surface_type type, float refraction_index, Vector center, float radius): Object(type), center(center), radius(radius)
{
    material = std::make_shared<Refracted_reflected_texture>(refraction_index);
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

std::shared_ptr<Texture_Material> Sphere::get_texture()
{
    return material;
}