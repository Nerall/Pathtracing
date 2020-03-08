#include "Path_tracing_texture.hpp"

Path_tracing_texture::Path_tracing_texture(float diffuse_ratio): diffuse_ratio(diffuse_ratio)
{
}

Ray Path_tracing_texture::get_random_ray(Ray &ray, Vector &hit_point, std::vector<Vector> &transformation_matrix)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> generate(0, 1);
    auto transformation_matrix = create_transformation_matrix(ray, hit_point);
    float n1 = generate(generator);
    float n2 = generate(generator);
    Vector direction_world_coordinate = get_random_direction(n1, n2);
    Vector direction_point_coordinate = direction_world_coordinate * transformation_matrix;
    return Ray(hit_point + 0 * direction_point_coordinate, direction_point_coordinate);
}

Vector Path_tracing_texture::get_random_direction(float n1, float n2)
{
    float sinTheta = sqrtf(1 - powf(n1, 2)); 
    float phi = 2 * M_PI * n2; 
    float x = sinTheta * cosf(phi); 
    float z = sinTheta * sinf(phi); 
    return Vector(x, n1, z);
}

std::vector<Vector> Path_tracing_texture::create_transformation_matrix(Ray &ray, Vector &hit_point)
{
    Vector new_x;
    if (std::fabs(ray.get_hit()->get_normal(hit_point).get_x()) > std::fabs(ray.get_hit()->get_normal(hit_point).get_y()))
        new_x = Vector(ray.get_hit()->get_normal(hit_point).get_z(), 0, ray.get_hit()->get_normal(hit_point).get_x() * -1).normalize();
    else
        new_x = Vector(0, ray.get_hit()->get_normal(hit_point).get_z() * -1, ray.get_hit()->get_normal(hit_point).get_y()).normalize();
    Vector new_z = (ray.get_hit()->get_normal(hit_point).cross_product(new_x)).normalize();
    std::vector<Vector> transformation_matrix{new_x, ray.get_hit()->get_normal(hit_point), new_z};
    return transformation_matrix;
}

Path_tracing_texture::~Path_tracing_texture()
{
}