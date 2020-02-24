#include "Sphere.hpp"

Sphere::Sphere(Vector color, Vector center, float radius): Object(color), center(center), radius(radius)
{
}

bool Sphere::collide(Ray &ray)
{
    float t0, t1;
    auto origin = ray.get_origin();
    auto direction = ray.get_direction();
    auto l = origin - center;
    auto a = direction.dot_product(direction);
    auto b = 2 * direction.dot_product(l);
    //std::cout << b << "\n";
    auto c = l.dot_product(l) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    //std::cout << discriminant << "\n";
    if (discriminant < 0)
        return false;
    else if (discriminant == 0)
        ray.set_t_distance(-b / (2 * a));
    else
    {
        t0 = -b - sqrt(discriminant) / 2 * a;
        t1 = -b + sqrt(discriminant) / 2 * a;
        ray.set_t_distance((t1 < t0) ? t1 : t0);
    }
    return true;
}