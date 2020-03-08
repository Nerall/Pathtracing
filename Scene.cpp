#include "Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, std::vector<Point_Light> lights, std::size_t height, std::size_t width): objects(objects), camera(camera), lights(lights), height(height), width(width)
{
    pixels = std::vector<std::vector<Vector>>{width, std::vector<Vector>(height, 0)};
}

Vector Scene::cast_ray(Ray &ray, std::size_t depth)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> generate(0, 1);
    Vector color(0);
    Vector total_light(0);
    if (trace(ray))
    {
        if (depth > 9)
            return color;
        auto refracted_reflected_texture = std::static_pointer_cast<Refracted_reflected_texture>(ray.get_hit()->get_texture());
        auto diffuse_texture = std::static_pointer_cast<Diffuse_texture>(ray.get_hit()->get_texture());
        auto diffuse_specular_texture = std::static_pointer_cast<Diffuse_specular>(ray.get_hit()->get_texture());
        auto hit_point = ray.get_hit_point();
        if (ray.get_hit()->get_surface_type() == Object::Surface_type::reflection)
        {
            Ray reflected_ray = refracted_reflected_texture->reflection_case(refracted_reflected_texture, ray, hit_point);
            color = cast_ray(reflected_ray, depth + 1);
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::diffuse)
        {
            for (size_t i = 0; i < lights.size(); i++)
            {
                Ray shadow_ray(hit_point + ray.get_hit()->get_normal(hit_point) * 0.1, lights[i].get_direction(hit_point) * -1);
                if (trace(shadow_ray) && lights[i].get_direction(hit_point).norm() > (hit_point - shadow_ray.get_hit_point()).norm())
                    continue;
                total_light += lights[i].illuminate(ray, hit_point);
            }
            color = (diffuse_texture->get_diffuse_ratio() / M_PI) * total_light;
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::diffuse_specular)
        {
            for (size_t i = 0; i < lights.size(); i++)
            {
                Ray shadow_ray(hit_point + ray.get_hit()->get_normal(hit_point) * 0.1, lights[i].get_direction(hit_point) * -1);
                if (trace(shadow_ray) && lights[i].get_direction(hit_point).norm() > (hit_point - shadow_ray.get_hit_point()).norm())
                    continue;
                color += diffuse_specular_texture->get_color_light(lights[i], ray, hit_point);
            }
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::refraction)
        {
            Ray refracted_ray = refracted_reflected_texture->create_refraction_ray(refracted_reflected_texture, ray, hit_point);
            color = cast_ray(refracted_ray, depth + 1);
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::reflection_refraction)
        {
            Vector refraction_color(0);
            float fresnel_ratio = refracted_reflected_texture->get_fresnel_ratio(ray, hit_point);
            if (fresnel_ratio < 1)
            {
                Ray refracted_ray = refracted_reflected_texture->create_refraction_ray(refracted_reflected_texture, ray, hit_point);
                Vector refraction_color = cast_ray(refracted_ray, depth + 1);
            }
            Ray reflected_ray = refracted_reflected_texture->create_reflection_ray(refracted_reflected_texture, ray, hit_point);
            Vector reflection_color = cast_ray(reflected_ray, depth + 1);
            color = fresnel_ratio * reflection_color + (1 - fresnel_ratio) * refraction_color;
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::path_tracing_texture)
        {
            Vector indirect_component(0);
            Vector direct_component(0);
            for (size_t i = 0; i < lights.size(); i++)
            {
                Ray shadow_ray(hit_point + ray.get_hit()->get_normal(hit_point) * 0.1, lights[i].get_direction(hit_point) * -1);
                if (trace(shadow_ray) && lights[i].get_direction(hit_point).norm() > (hit_point - shadow_ray.get_hit_point()).norm())
                    continue;
                direct_component += lights[i].illuminate(ray, hit_point);
            }
            std::size_t number_of_rays = 3;
            auto transformation_matrix = create_transformation_matrix(ray, hit_point);
            for (size_t i = 0; i < number_of_rays; i++)
            {
                float n1 = generate(generator);
                float n2 = generate(generator);
                Vector direction_world_coordinate = get_random_direction(n1, n2);
                Vector direction_point_coordinate = direction_world_coordinate * transformation_matrix;
                Ray new_ray(hit_point + 0 * direction_point_coordinate, direction_point_coordinate);
                indirect_component += (n1 * cast_ray(new_ray, depth + 1)) / (1 / (2 * M_PI));
            }
            indirect_component /= number_of_rays;
            color = (indirect_component + direct_component) * diffuse_texture->get_diffuse_ratio();
        }
    }
    else
        return Vector(1);
    return color.adjust();
}

Vector Scene::get_random_direction(float n1, float n2)
{
    float sinTheta = sqrtf(1 - powf(n1, 2)); 
    float phi = 2 * M_PI * n2; 
    float x = sinTheta * cosf(phi); 
    float z = sinTheta * sinf(phi); 
    return Vector(x, n1, z); 
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
            char r = (char)(255 * pixels[j][i].get_x()); 
            char g = (char)(255 * pixels[j][i].get_y()); 
            char b = (char)(255 * pixels[j][i].get_z()); 
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

std::vector<Vector> Scene::create_transformation_matrix(Ray &ray, Vector &hit_point)
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

Scene::~Scene()
{
}