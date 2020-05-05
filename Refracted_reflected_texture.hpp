#pragma once

#include "Ray.hpp"
#include "Texture_Material.hpp"
#include "Object.hpp"
#include <algorithm>

class Refracted_reflected_texture: public Texture_Material
{
private:
    float refraction_ratio;

public:
    Refracted_reflected_texture(float refraction_ratio);
    float get_fresnel_ratio(Ray const& ray, Vector const& hit_point);
    Vector get_refraction_direction(Ray const& ray, Vector const& hit_point);
    Vector get_reflection_direction(Ray const& ray, Vector const& hit_point);
    Ray create_refraction_ray(std::shared_ptr<Refracted_reflected_texture> texture, Ray const& ray, Vector const& hit_point);
    Ray create_reflection_ray(std::shared_ptr<Refracted_reflected_texture> texture, Ray const& ray, Vector const& hit_point);
    Ray reflection_case(std::shared_ptr<Refracted_reflected_texture> refracted_reflected_texture, Ray const& ray, Vector const& hit_point);
    ~Refracted_reflected_texture();
};


