#include "Light.hpp"

class Distant_light: public Light
{
private:
    Vector direction;

public:
    Distant_light(Vector color, float intensity, Vector direction);
    Vector get_direction();
    float get_intensity();
    ~Distant_light();
};


