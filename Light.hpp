#include "Vector.hpp"
#include <vector>

class Light
{
private:
    Vector location;
    std::vector<Vector> rays;

public:
    Light(Vector location, std::vector<Vector> rays);
    virtual ~Light() = 0;
};


