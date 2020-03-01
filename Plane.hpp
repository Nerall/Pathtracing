#include "Object.hpp"
#include "Diffuse_texture.hpp"
#include "Refracted_reflected_texture.hpp"
#include "Ray.hpp"
#include <cmath>

class Plane: public Object
{
private:
    Vector point;
    Vector normal;

public:
    Plane(Surface_type type, float diffuse_ratio, Vector point, Vector normal);
    Plane(Surface_type type, float refraction_index, Vector point, Vector normal);
    bool collide(Ray &ray) override;
    Vector get_normal(Vector &p) override;
    std::shared_ptr<Texture_Material> get_texture() override;
};