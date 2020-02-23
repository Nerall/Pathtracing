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
    Image image;
    std::shared_ptr<Object> hit;
    std::vector<Vector> buffer;

public:
    Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, Image image);
    bool trace(Ray &ray);
    std::shared_ptr<Object> get_hit();
    std::vector<Vector> get_buffer();
    Vector cast_ray(Ray &ray);
    void save_image();
    Image get_image();
    void render();
    ~Scene();
};