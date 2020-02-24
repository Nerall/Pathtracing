#pragma once

#include <vector>
#include <memory>
#include "Object.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Image.hpp"
#include <limits>

class Scene
{
private:
    std::vector<std::shared_ptr<Object>> objects;
    Camera camera;
    std::size_t height;
    std::size_t width;
    std::shared_ptr<Object> hit;
    std::vector<std::vector<Vector>> pixels;

public:
    Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, std::size_t height, std::size_t width);
    bool trace(Ray &ray);
    std::shared_ptr<Object> get_hit();
    std::vector<std::vector<Vector>> get_pixels();
    Vector cast_ray(Ray &ray);
    void save_image();
    void render();
    ~Scene();
};