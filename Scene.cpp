#include "Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, std::vector<Point_Light> lights, std::size_t height, std::size_t width): objects(objects), camera(camera), lights(lights), height(height), width(width)
{
    pixels = std::vector<std::vector<Vector>>{width, std::vector<Vector>(height, 0)};
}

Vector Scene::cast_ray(Ray &ray, std::size_t depth)
{
    Vector color(0);
    if (depth > 9)
        return color;
    Vector total_light(0);
    if (trace(ray))
    {
        auto refracted_reflected_texture = std::static_pointer_cast<Refracted_reflected_texture>(ray.get_hit()->get_texture());
        auto diffuse_texture = std::static_pointer_cast<Diffuse_texture>(ray.get_hit()->get_texture());
        auto hit_point = ray.get_hit_point();
        if (ray.get_hit()->get_surface_type() == Object::Surface_type::reflection)
        {
            Ray reflected_ray = refracted_reflected_texture->reflection_case(refracted_reflected_texture, ray, hit_point);
            color = cast_ray(reflected_ray, depth + 1);
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::diffuse)
        {
            for (size_t i = 0; i < lights.size(); i++)
                total_light += lights[i].illuminate(ray, hit_point);
            color = (diffuse_texture->get_diffuse_ratio() / M_PI) * total_light;
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::refraction)
        {
            Ray refracted_ray = refracted_reflected_texture->create_refraction_ray(refracted_reflected_texture, ray, hit_point);
            color = cast_ray(refracted_ray, depth + 1);
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::reflection_refraction)
        {
            
            float fresnel_ratio = refracted_reflected_texture->get_fresnel_ratio(ray, hit_point);
            if (fresnel_ratio < 1)
            {
                Ray refracted_ray = refracted_reflected_texture->create_refraction_ray(refracted_reflected_texture, ray, hit_point);
                Vector refraction_color = cast_ray(refracted_ray, depth + 1);
            }
            Ray reflected_ray = refracted_reflected_texture->create_reflection_ray(refracted_reflected_texture, ray, hit_point);
            Vector reflection_color = cast_ray(reflected_ray, depth + 1);
            color = fresnel_ratio * reflection_color + (1 - fresnel_ratio) * reflection_color;
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