#include "Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, std::vector<Point_Light> lights, std::size_t height, std::size_t width): objects(objects), camera(camera), lights(lights), height(height), width(width)
{
    pixels = std::vector<std::vector<Vector>>{width, std::vector<Vector>(height, 0)};
}

Vector Scene::cast_ray(Ray &ray)
{
    auto hit_point = ray.get_hit_point();
    Vector total_light;
    if (trace(ray))
    {
        for (size_t i = 0; i < lights.size(); i++)
            total_light += lights[i].get_illumination(hit_point);
        return (ray.get_hit()->get_texture() / M_PI) * total_light;
    }
    return Vector(0, 0, 0);
}

bool Scene::trace(Ray &ray)
{
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        if ((*it)->collide(ray))
        {
            if (ray.get_t_distance() < ray.get_nearest())
            {
                ray.set_nearest(ray.get_t_distance());
                ray.set_hit(*it);
            }
        }
    }
    ray.set_t_distance(ray.get_nearest());
    return (ray.get_hit() != nullptr);
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
            char r = (char)pixels[i][j].get_x(); 
            char g = (char)pixels[i][j].get_y(); 
            char b = (char)pixels[i][j].get_z(); 
            ofs << r << g << b;
        }
    }
    ofs.close();
}

void Scene::render()
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            float x = (2 * (i + 0.5) / width - 1); 
            float y = (1 - 2 * (j + 0.5) / height);
            Vector v(x, y, -1);
            Ray r = camera.create_ray(x, y);
            pixels[i][j] = cast_ray(r);
        }
    }
}

Scene::~Scene()
{
}