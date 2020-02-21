#include <cmath>
#include "Color.hpp"

class Vector
{
private:
    float x;
    float y;
    float z;

public:
    Vector(float x, float y, float z);
    float magnitude();
    Vector unit_vector();
    Vector operator+(Vector const &rhs);
    Vector operator-(Vector const &rhs);
    Vector operator*(float scalar);
    float dot_product(Vector const &rhs);
    Vector cross_product(Vector const &rhs);
    float norm();
    Vec3 normalize();
    ~Vector();
};


