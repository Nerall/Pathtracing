#include "Vector.hpp"

class Camera
{
private:
    Vector center;
    Vector direction;
    Vector height;
    float fov_x;
    float fov_y;
    float z_min;

public:
    Camera(Vector center, Vector direction, Vector height, float fov_x, float fov_y, float z_min);
    ~Camera();
};


