#include "Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, std::size_t height, std::size_t width): objects(objects), camera(camera), height(height), width(width), hit(nullptr)
{
    pixels = std::vector<std::vector<Vector>>{height, std::vector<Vector>(width, 0)};
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

std::vector<std::vector<Vector>> Scene::get_pixels()
{
    return pixels;
}

void Scene::save_image()
{
    std::ofstream ofs ("image.ppm", std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            auto r = pixels[i][j].get_x(); 
            auto g = pixels[i][j].get_y(); 
            auto b = pixels[i][j].get_z(); 
            ofs << r << g << b;
        }
    }
}

void Scene::render()
{
    float scale = tan(camera.get_fov() * 0.5 * (M_PI / 180)); 
    float imageAspectRatio = width / height;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            float x = (2 * (i + 0.5) / width - 1) * imageAspectRatio * scale; 
            float y = (1 - 2 * (j + 0.5) / height) * scale;
            Vector v(x, y, -1);
            Ray r(camera.get_origin(), v.normalize());
            pixels[i][j] = cast_ray(r);
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