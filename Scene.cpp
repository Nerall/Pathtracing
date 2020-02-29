#include "Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, std::vector<Point_Light> lights, std::size_t height, std::size_t width): objects(objects), camera(camera), lights(lights), height(height), width(width)
{
    pixels = std::vector<std::vector<Vector>>{width, std::vector<Vector>(height, 0)};
}

Vector Scene::cast_ray(Ray &ray, std::size_t depth)
{
    Vector color(0);
    if (depth > 4)
        return color;
    Vector total_light(0);
    if (trace(ray))
    {
        auto hit_point = ray.get_hit_point();
        if (ray.get_hit()->get_surface_type() == Object::Surface_type::reflection)
        {
            auto direction_reflection_ray = ray.get_direction() - 2 * ray.get_hit()->get_normal(hit_point) * ray.get_hit()->get_normal(hit_point).dot_product(ray.get_direction());
            Ray reflect_ray(hit_point, direction_reflection_ray);
            color = cast_ray(reflect_ray, depth + 1);
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::diffuse)
        {
            for (size_t i = 0; i < lights.size(); i++)
                total_light += lights[i].illuminate(ray, hit_point);
            color = (ray.get_hit()->get_texture() / M_PI) * total_light;
        }
    }
    return color;
}

bool Scene::trace(Ray &ray)
{
    for (std::size_t i = 0; i < objects.size(); i++)
    {
        if (objects[i]->collide(ray))
        {
            if (ray.get_t_distance() < ray.get_nearest())
            {
                ray.set_nearest(ray.get_t_distance());
                ray.set_hit(objects[i]);
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
            char r = (char)pixels[j][i].get_x(); 
            char g = (char)pixels[j][i].get_y(); 
            char b = (char)pixels[j][i].get_z(); 
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
            float x = (2 * (j + 0.5) / width - 1); 
            float y = (1 - 2 * (i + 0.5) / height);
            Ray r = camera.create_ray(x, y);
            pixels[j][i] = cast_ray(r, 1);
        }
    }
}

Scene::~Scene()
{
}