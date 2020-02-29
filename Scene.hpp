#pragma once

#include <vector>
#include <memory>
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
    std::vector<Point_Light> lights;
    std::size_t height;
    std::size_t width;
    std::vector<std::vector<Vector>> pixels;

public:
    Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, std::vector<Point_Light> lights, std::size_t height, std::size_t width);
    bool trace(Ray &ray);
    std::vector<std::vector<Vector>> get_pixels();
    Vector cast_ray(Ray &ray);
    void save_image();
    void render();
    ~Scene();
};