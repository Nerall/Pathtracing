#include "Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, std::vector<Point_Light> pointLights, std::size_t height, std::size_t width): objects(objects), camera(camera), pointLights(pointLights), height(height), width(width), distantLightExist(false)
{
    pixels = std::vector<std::vector<Vector>>{width, std::vector<Vector>(height, 0)};
}

Scene::Scene(std::vector<std::shared_ptr<Object>> objects, Camera camera, Distant_light distantLight, std::size_t height, std::size_t width): objects(objects), camera(camera), distantLight(distantLight), height(height), width(width), distantLightExist(true)
{
    pixels = std::vector<std::vector<Vector>>{width, std::vector<Vector>(height, 0)};
    pointLights = std::vector<Point_Light>();
}

Vector Scene::cast_ray_pathtracing(Ray &ray, std::size_t depth)
{
    static std::default_random_engine generator;
    std::uniform_real_distribution<float> generate(0.f, 1.f);
    Vector color(0);
    Vector total_light(0);
    if (trace(ray))
    {
        if ((ray.getOriginObject() && ray.get_hit()->get_surface_type() != Object::Surface_type::REFRACTION && ray.get_hit()->get_surface_type() != Object::Surface_type::REFLECTION_REFRACTION) || depth > 3)
            return Vector(0.0);

        auto hit_point = ray.get_hit_point();
        Vector indirect_component(0);
        Vector direct_component(0);
        std::size_t number_of_rays = 3;
        auto transformation_matrix = create_transformation_matrix(ray, hit_point);
        for (size_t i = 0; i < number_of_rays; i++)
        {
            float n1 = generate(generator);
            float n2 = generate(generator);

            Vector direction_world_coordinate = get_random_direction_diffuse(n1, n2);
            Vector direction_point_coordinate = transformation_matrix * direction_world_coordinate;

            Ray new_ray_direct(hit_point + 0.1 * direction_point_coordinate, direction_point_coordinate, ray.get_hit());
            Ray new_ray_indirect(hit_point + 0.1 * direction_point_coordinate, direction_point_coordinate);

            direct_component += n1 * cast_ray_pathtracing(new_ray_direct, depth + 1);
            indirect_component += n1 * cast_ray_pathtracing(new_ray_indirect, depth + 1);
        }
        indirect_component /= number_of_rays;
        direct_component /= number_of_rays;
        color = (indirect_component + direct_component) * 0.36;
        //color = ((2 * indirect_component) + (direct_component / M_PI)) * 0.18;
    }
    else
    {
        if (ray.getOriginObject())
        {
            auto refracted_reflected_texture = std::static_pointer_cast<Refracted_reflected_texture>(ray.getOriginObject()->get_texture());
            auto diffuse_texture = std::static_pointer_cast<Diffuse_texture>(ray.getOriginObject()->get_texture());
            auto phong_texture = std::static_pointer_cast<Phong>(ray.getOriginObject()->get_texture());
            if (ray.getOriginObject()->get_surface_type() == Object::Surface_type::REFLECTION)
            {
                Ray viewRay(camera.get_origin(), (ray.get_origin() - camera.get_origin()).normalize());
                viewRay.set_hit(ray.getOriginObject());
                Ray reflected_ray = refracted_reflected_texture->reflection_case(refracted_reflected_texture, viewRay, ray.get_origin());
                return cast_ray_raytracing(reflected_ray, depth + 1, true);
            }
            else if (ray.getOriginObject()->get_surface_type() == Object::Surface_type::DIFFUSE)
            {
                return distantLight.illuminateOrigin(ray, ray.get_origin());
            }
            else if (ray.getOriginObject()->get_surface_type() == Object::Surface_type::PHONG)
            {
                Ray viewRay(camera.get_origin(), (ray.get_origin() - camera.get_origin()).normalize());
                viewRay.set_hit(ray.getOriginObject());
                return phong_texture->get_color_light(distantLight, viewRay, ray.get_origin());
            }
            else if (ray.getOriginObject()->get_surface_type() == Object::Surface_type::REFRACTION)
            {
                Ray viewRay(camera.get_origin(), (ray.get_origin() - camera.get_origin()).normalize());
                viewRay.set_hit(ray.getOriginObject());
                Ray refracted_ray = refracted_reflected_texture->create_refraction_ray(refracted_reflected_texture, viewRay, ray.get_origin());
                return cast_ray_raytracing(refracted_ray, depth + 1, true);
            }
            else if (ray.getOriginObject()->get_surface_type() == Object::Surface_type::REFLECTION_REFRACTION)
            {
                Ray viewRay(camera.get_origin(), (ray.get_origin() - camera.get_origin()).normalize());
                viewRay.set_hit(ray.getOriginObject());
                Vector refraction_color(0);
                float fresnel_ratio = refracted_reflected_texture->get_fresnel_ratio(viewRay, ray.get_origin());
                if (fresnel_ratio < 1)
                {
                    Ray refracted_ray = refracted_reflected_texture->create_refraction_ray(refracted_reflected_texture, viewRay, ray.get_origin());
                    refraction_color = cast_ray_raytracing(refracted_ray, depth + 1, true);
                }
                Ray reflected_ray = refracted_reflected_texture->create_reflection_ray(refracted_reflected_texture, viewRay, ray.get_origin());
                Vector reflection_color = cast_ray_raytracing(reflected_ray, depth + 1, true);
                return fresnel_ratio * reflection_color + (1 - fresnel_ratio) * refraction_color;
            }
        }
        else
            return Vector(0.0);
    }
    return color.adjust();
}

Vector Scene::cast_ray_raytracing(Ray &ray, std::size_t depth, bool comesFromPath)
{
    Vector color(0);
    Vector total_light(0);
    if (trace(ray))
    {
        if (depth > 5)
            return Vector(0.0);

        auto hit_point = ray.get_hit_point();
        auto refracted_reflected_texture = std::static_pointer_cast<Refracted_reflected_texture>(ray.get_hit()->get_texture());
        auto diffuse_texture = std::static_pointer_cast<Diffuse_texture>(ray.get_hit()->get_texture());
        auto phong_texture = std::static_pointer_cast<Phong>(ray.get_hit()->get_texture());
        auto path_tracing_texture = std::static_pointer_cast<Path_tracing_texture>(ray.get_hit()->get_texture());
        if (ray.get_hit()->get_surface_type() == Object::Surface_type::REFLECTION)
        {
            Ray reflected_ray = refracted_reflected_texture->reflection_case(refracted_reflected_texture, ray, hit_point);
            color += cast_ray_raytracing(reflected_ray, depth + 1, false);
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::DIFFUSE)
        {
            for (size_t i = 0; i < pointLights.size(); i++)
            {
                Ray shadow_ray(hit_point + ray.get_hit()->get_normal(hit_point) * 0.1f, pointLights[i].get_direction(hit_point) * -1);
                if ((trace(shadow_ray) && shadow_ray.get_hit()->get_surface_type() != Object::Surface_type::REFRACTION && shadow_ray.get_hit()->get_surface_type() != Object::Surface_type::REFLECTION_REFRACTION) && pointLights[i].get_direction(hit_point).norm() > (hit_point - shadow_ray.get_hit_point()).norm())
                    continue;
                color += pointLights[i].illuminate(ray, hit_point);
            }
            if (distantLightExist)
            {
                Ray shadow_ray(hit_point + ray.get_hit()->get_normal(hit_point) * 0.1, distantLight.get_direction() * -1);
                if (!trace(shadow_ray) || (shadow_ray.get_hit()->get_surface_type() == Object::Surface_type::REFRACTION || shadow_ray.get_hit()->get_surface_type() == Object::Surface_type::REFLECTION_REFRACTION))
                {
                    color += distantLight.illuminate(ray, hit_point);
                    if (!comesFromPath)
                        color *= (diffuse_texture->get_diffuse_ratio() / M_PI);
                }
            }
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::PHONG)
        {
            for (size_t i = 0; i < pointLights.size(); i++)
            {
                Ray shadow_ray(hit_point + ray.get_hit()->get_normal(hit_point) * 0.1, pointLights[i].get_direction(hit_point) * -1);
                if ((trace(shadow_ray) && shadow_ray.get_hit()->get_surface_type() != Object::Surface_type::REFRACTION && shadow_ray.get_hit()->get_surface_type() != Object::Surface_type::REFLECTION_REFRACTION) && pointLights[i].get_direction(hit_point).norm() > (hit_point - shadow_ray.get_hit_point()).norm())
                    continue;
                color += phong_texture->get_color_light(pointLights[i], ray, hit_point);
            }
            if (distantLightExist)
            {
                Ray shadow_ray(hit_point + ray.get_hit()->get_normal(hit_point) * 0.1, distantLight.get_direction() * -1);
                if (!trace(shadow_ray) || (shadow_ray.get_hit()->get_surface_type() == Object::Surface_type::REFRACTION || shadow_ray.get_hit()->get_surface_type() == Object::Surface_type::REFLECTION_REFRACTION))
                    color += phong_texture->get_color_light(distantLight, ray, hit_point);
            }
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::REFRACTION)
        {
            Ray refracted_ray = refracted_reflected_texture->create_refraction_ray(refracted_reflected_texture, ray, hit_point);
            color = cast_ray_raytracing(refracted_ray, depth + 1, false);
        }
        else if (ray.get_hit()->get_surface_type() == Object::Surface_type::REFLECTION_REFRACTION)
        {
            Vector refraction_color(0);
            float fresnel_ratio = refracted_reflected_texture->get_fresnel_ratio(ray, hit_point);
            if (fresnel_ratio < 1)
            {
                Ray refracted_ray = refracted_reflected_texture->create_refraction_ray(refracted_reflected_texture, ray, hit_point);
                refraction_color = cast_ray_raytracing(refracted_ray, depth + 1, false);
            }
            Ray reflected_ray = refracted_reflected_texture->create_reflection_ray(refracted_reflected_texture, ray, hit_point);
            Vector reflection_color = cast_ray_raytracing(reflected_ray, depth + 1, false);
            color = fresnel_ratio * reflection_color + (1 - fresnel_ratio) * refraction_color;
        }
    }
    else
        return Vector(0.0);
    if (!comesFromPath)
        return color.adjust();
    else
        return color;
}

Vector Scene::get_random_direction_diffuse(float n1, float n2)
{
    float sinTheta = sqrtf(1 - powf(n1, 2)); 
    float phi = 2 * M_PI * n2; 
    float x = sinTheta * cosf(phi); 
    float z = sinTheta * sinf(phi); 
    return Vector(x, n1, z).normalize(); 
}

Vector Scene::get_random_direction_diffuse_v2(float n1, float n2)
{
    float sinTheta = sqrtf(1 - powf(n1, 2)); 
    float phi = 2 * M_PI * n2; 
    float x = sinTheta * cosf(phi); 
    float z = sinTheta * sinf(phi); 
    return Vector(x, n1, z).normalize(); 
}

Vector Scene::get_random_direction_specular(float n1, float n2)
{
    float sinTheta = sqrtf(1 - powf(n1, 2)); 
    float phi = 2 * M_PI * n2; 
    float x = sinTheta * cosf(phi); 
    float z = sinTheta * sinf(phi); 
    return Vector(x, n1, z).normalize(); 
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

void Scene::render(RenderingMethod const& renderingMethod)
{
    if (renderingMethod == Scene::RenderingMethod::RAYTRACING)
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                float x = (2 * (j + 0.5) / width - 1); 
                float y = (1 - 2 * (i + 0.5) / height);
                Ray r = camera.create_ray(x, y);
                pixels[j][i] = cast_ray_raytracing(r, 1, false);
            }
        }
    }
    else if (renderingMethod == Scene::RenderingMethod::PATHTRACING)
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                float x = (2 * (j + 0.5) / width - 1); 
                float y = (1 - 2 * (i + 0.5) / height);
                Ray r = camera.create_ray(x, y);
                pixels[j][i] = cast_ray_pathtracing(r, 1);
            }
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