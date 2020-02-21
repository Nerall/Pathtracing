#include "Vector.hpp"

Vector::Vector(float x, float y, float z): x(x), y(y), z(z)
{
}

Vector::~Vector()
{
}

float Vector::magnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector Vector::unit_vector()
{
    return Vector(this->x / this->magnitude(), this->y / this->magnitude(), this->z / this->magnitude());
}

Vector Vector::operator+(Vector const &rhs)
{
    return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector Vector::operator-(Vector const &rhs)
{
    return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector Vector::operator*(float scalar)
{
    this->x *scalar;
    this->y *scalar;
    this->z *scalar;
    return *this;
}

float Vector::dot_product(Vector const &rhs)
{
    return this->x * rhs.x + this->y + rhs.y + this->z + rhs.z;
}

Vector Vector::cross_product(Vector const &rhs)
{
    return Vector(this->y * rhs.z - this->z * rhs.y, this->x * rhs.z - this->z * rhs.x, this->x * rhs.y - this->y * rhs.x);
}

float Vector::norm()
{
    return sqrt(dot_product(*this));
}

Vec3 Vector::normalize()
{
    return (*this)*(1/norm());
}