#include "Refracted_reflected_texture.hpp"

Refracted_reflected_texture::Refracted_reflected_texture(float refraction_ratio): refraction_ratio(refraction_ratio)
{
}

Ray Refracted_reflected_texture::reflection_case(std::shared_ptr<Refracted_reflected_texture> refracted_reflected_texture, Ray &ray, Vector &hit_point)
{
    Vector reflected_direction = refracted_reflected_texture->get_reflection_direction(ray, hit_point);
    Ray reflected_ray(hit_point, reflected_direction);
    return reflected_ray;
}

Vector Refracted_reflected_texture::get_reflection_direction(Ray &ray, Vector &hit_point)
{
    return (ray.get_direction() - 2 * ray.get_hit()->get_normal(hit_point) * ray.get_hit()->get_normal(hit_point).dot_product(ray.get_direction())).normalize();
}

Ray Refracted_reflected_texture::create_refraction_ray(std::shared_ptr<Refracted_reflected_texture> texture, Ray &ray, Vector &hit_point)
{
    float cos_incident = ray.get_direction().dot_product(ray.get_hit()->get_normal(hit_point));
    Vector refraction_direction = texture->get_refraction_direction(ray, hit_point).normalize();
    Vector refracted_origin(0);
    if (cos_incident < 0)
        refracted_origin = hit_point - 0.095 * ray.get_hit()->get_normal(hit_point);
    else
        refracted_origin = hit_point + 0.095 * ray.get_hit()->get_normal(hit_point);
    Ray refracted_ray(refracted_origin, refraction_direction);
    return refracted_ray;
}

Ray Refracted_reflected_texture::create_reflection_ray(std::shared_ptr<Refracted_reflected_texture> texture, Ray &ray, Vector &hit_point)
{
    float cos_incident = ray.get_direction().dot_product(ray.get_hit()->get_normal(hit_point));
    Vector reflection_direction = texture->get_reflection_direction(ray, hit_point);
    Vector reflected_origin(0);
    if (cos_incident < 0)
        reflected_origin = hit_point + 0.5 * ray.get_hit()->get_normal(hit_point);
    else
        reflected_origin = hit_point - 0.5 * ray.get_hit()->get_normal(hit_point);
    Ray reflected_ray(reflected_origin, reflection_direction);
    return reflected_ray;
}

Vector Refracted_reflected_texture::get_refraction_direction(Ray &ray, Vector &hit_point)
{
    float cos_incident = std::clamp(ray.get_hit()->get_normal(hit_point).dot_product(ray.get_direction()), -1.f, 1.f);
    float coming_refraction_ratio = 1;
    float leaving_refraction_ratio = refraction_ratio;
    if (cos_incident < 0)
        cos_incident *= -1;
    else
        std::swap(coming_refraction_ratio, leaving_refraction_ratio);
    float refraction_index = coming_refraction_ratio / leaving_refraction_ratio;
    float cos_refracted2 = 1 - (powf(refraction_index, 2) * (1 - powf(cos_incident, 2)));
    if (cos_refracted2 < 0)
        return Vector(0);
    else
    {
        return (refraction_index * ray.get_direction() + (refraction_index * cos_incident - sqrtf(cos_refracted2)) * (ray.get_hit()->get_normal(hit_point) * -1)).normalize();
    }
}

float Refracted_reflected_texture::get_fresnel_ratio(Ray &ray, Vector &hit_point)
{
    float coming_refraction_ratio = 1;
    float leaving_refraction_ratio = refraction_ratio;
    float cos_incident = std::clamp(ray.get_hit()->get_normal(hit_point).dot_product(ray.get_direction()), -1.f, 1.f);
    if (cos_incident > 0)
        std::swap(coming_refraction_ratio, leaving_refraction_ratio);
    float refraction_index = coming_refraction_ratio / leaving_refraction_ratio;
    float sinus_refracted = refraction_index * sqrt(std::max(0.f, 1 - powf(cos_incident, 2)));
    if (sinus_refracted >= 1)
        return 1;
    else
    {
        float cos_refracted = sqrt(std::max(0.f, 1 - powf(sinus_refracted, 2)));
        cos_incident = fabsf(cos_incident);
        float parallel_light = powf((coming_refraction_ratio * cos_incident - leaving_refraction_ratio * cos_refracted) / (coming_refraction_ratio * cos_incident + leaving_refraction_ratio * cos_refracted), 2);
        float perpendicular_light = powf((coming_refraction_ratio * cos_refracted - leaving_refraction_ratio * cos_incident) / (coming_refraction_ratio * cos_refracted + leaving_refraction_ratio * cos_incident), 2);
        return (perpendicular_light + parallel_light) / 2;
    }
}

Refracted_reflected_texture::~Refracted_reflected_texture()
{
}