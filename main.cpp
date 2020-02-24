#include "Image.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "Vector.hpp"
#include "Light.hpp"
#include "Point_Light.hpp"
#include <memory>
#include <vector>


int main()
{
    Vector origin(0, 0, 0);
    Vector sphere_center(0, 0, -2);
    Vector color(255, 0, 0);
    Camera camera(origin, 51.52);
    Sphere sphere(color, sphere_center, 0.4);
    std::shared_ptr<Object> sphere_ptr = std::make_shared<Sphere>(sphere);
    std::vector<std::shared_ptr<Object>> objects{};
    objects.push_back(sphere_ptr);
    Scene scene(objects, camera, 480, 640);
    scene.render();
    scene.save_image();
    return 0;
}
