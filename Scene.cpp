#include "Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, Image image): objects(objects), camera(camera), image(image), hit(nullptr)
{
    buffer = std::vector<Vector>{};
}

Vector Scene::cast_ray(Ray &ray)
{
    if (trace(ray))
        return hit->get_color();
    return Vector(0, 0, 0);
}

bool Scene::trace(Ray &ray)
{
    hit = nullptr;
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        if ((*it)->collide(ray))
        {
            if (ray.get_t_distance() < ray.get_nearest())
            {
                ray.set_nearest(ray.get_t_distance());
                hit = *it;
            }
        }
    }
    return (hit != nullptr); 
}

std::vector<Vector> Scene::get_buffer()
{
    return buffer;
}

Image Scene::get_image()
{
    return image;
}

void Scene::save_image()
{
    std::ofstream ofs ("image.ppm", std::ios::binary);
    ofs << "P6\n" << image.get_width() << " " << image.get_height() << "\n255\n";
    for (size_t i = 0; i < buffer.size(); i++)
    {
        auto r = (255 * buffer[i].get_x()); 
        auto g = (255 * buffer[i].get_y()); 
        auto b = (255 * buffer[i].get_z()); 
        ofs << r << g << b;
    }
    
}

void Scene::render()
{
    for (size_t i = 0; i < image.get_height(); i++)
    {
        for (size_t j = 0; j < image.get_width(); j++)
        {
            Ray r(camera.get_origin(), image.get_pixels()[i][j]);
            buffer.push_back(cast_ray(r));
        }
    }
}

std::shared_ptr<Object> Scene::get_hit()
{
    return hit;
}

Scene::~Scene()
{
}