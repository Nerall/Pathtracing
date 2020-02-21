#include "Light.hpp"

class Point_Light: public Light
{
private:
    /* data */
public:
    Point_Light(Vector location, std::vector<Vector> rays);
    ~Point_Light();
};