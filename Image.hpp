#include <vector>
#include "Vector.hpp"

class Image
{
private:
    int height;
    int width;
    std::vector<std::vector<Vector>> pixels;

public:
    Image(int height, int width, std::vector<std::vector> pixels);
    void save_image();
    ~Image();
};