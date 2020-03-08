#include "Object.hpp"
#include "Diffuse_texture.hpp"
#include "Diffuse_specular.hpp"
#include "Path_tracing_texture.hpp"
#include "Refracted_reflected_texture.hpp"
#include "Ray.hpp"
#include <cmath>

class Plane: public Object
{
private:
    Vector point;
    Vector normal;

public:
    Plane(Surface_type type, Vector point, Vector normal, std::shared_ptr<Diffuse_texture> texture, Vector color);
    Plane(Surface_type type, Vector point, Vector normal, std::shared_ptr<Refracted_reflected_texture> texture, Vector color);
    Plane(Surface_type type, Vector point, Vector normal, std::shared_ptr<Diffuse_specular> texture, Vector color);
    Plane(Surface_type type, Vector point, Vector normal, std::shared_ptr<Path_tracing_texture> texture, Vector color);
    bool collide(Ray &ray) override;
    Vector get_normal(Vector &p) override;
    std::shared_ptr<Texture_Material> get_texture() override;
};