#pragma once

#include "Texture_Material.hpp"
#include "Point_Light.hpp"
#include <random>

class Path_tracing_texture: public Texture_Material
{
private:
    float diffuse_ratio;

public:
    Path_tracing_texture(float diffuse_ratio);
    Ray get_random_ray(Ray &ray, Vector &hit_point, std::vector<Vector> &transformation_matrix);
    Vector get_random_direction(float n1, float n2);
    std::vector<Vector> create_transformation_matrix(Ray &ray, Vector &hit_point);
    ~Path_tracing_texture();
};


