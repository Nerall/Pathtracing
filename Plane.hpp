#include "Object.hpp"
#include "Ray.hpp"
#include <cmath>

class Plane: public Object
{
private:
    Vector point;
    Vector normal;

public:
    Plane(Surface_type type, float diffuse_ratio, float refraction_index, Vector point, Vector normal);
    bool collide(Ray &ray);
    Vector get_normal(Vector &p) override;
    float get_texture();
};