#include "Object.hpp"
#include "Ray.hpp"
#include <cmath>

class Plane: public Object
{
private:
    Vector point;
    Vector normal;
    Uniform_Texture texture;

public:
    Plane(Vector point, Vector normal, float reflection_ratio = 0.18);
    bool collide(Ray &ray);
    Vector get_normal(Vector &p) override;
    float get_texture();
    ~Plane();
};