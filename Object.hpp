#include "Vector.hpp"
#include "Ray.hpp"
#include "Uniform_Texture.hpp"

class Object
{
private:
    /* data */
public:
    Object(/* args */);
    virtual bool collide(Ray const& ray, float t) = 0;
    virtual Vector get_normale(Vector const &v1, Vector const &v2) = 0;
    virtual Uniform_Texture get_texture() = 0;
    ~Object();
};


