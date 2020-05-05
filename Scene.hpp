#pragma once

#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include "Object.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Image.hpp"
#include "Vector.hpp"
#include "Point_Light.hpp"
#include "Distant_light.hpp"
#include <limits>

class Scene
{
private:
    std::vector<std::shared_ptr<Object>> objects;
    Camera camera;
    std::vector<Point_Light> pointLights;
    Distant_light distantLight;
    std::size_t height;
    std::size_t width;
    std::vector<std::vector<Vector>> pixels;
    bool distantLightExist;

public:
    enum class RenderingMethod
    {
        RAYTRACING,
        PATHTRACING
    };

    Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, std::vector<Point_Light> pointLights, std::size_t height, std::size_t width);
    Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, Distant_light distantLight, std::size_t height, std::size_t width);
    bool trace(Ray &ray);
    std::vector<std::vector<Vector>> get_pixels();
    Vector cast_ray_pathtracing(Ray &ray, std::size_t depth);
    Vector cast_ray_raytracing(Ray &ray, std::size_t depth, bool comesFromPath);
    void save_image();
    void render(RenderingMethod const &renderingMethod);
    Vector get_random_direction_diffuse(float n1, float n2);
    Vector get_random_direction_diffuse_v2(float n1, float n2);
    Vector get_random_direction_specular(float n1, float n2);
    std::vector<Vector> create_transformation_matrix(Ray &ray, Vector &hit_point);
    ~Scene();
};