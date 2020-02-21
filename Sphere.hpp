#include "Object.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Sphere: public Object
{
private:
    Vector center;
    float radius;

public:
    Sphere(/* args */);
    ~Sphere();
};


