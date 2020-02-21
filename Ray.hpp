#include "Vector.hpp"

class Ray
{
private:
    Vector origin;
    Vector direction;
    Color color;

public:
    Ray(Vector origin, Vector direction, Color color);
    Vector get_origin();
    Vector get_direction();
    ~Ray();
};


