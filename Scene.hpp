#include <vector>

class Scene
{
private:
    std::vector<object> objects;
    std::vector<light> lights;
    camera camera;

public:
    Scene(std::vector<object> objects, std::vector<light> lights, camera camera);
    ~Scene();
};