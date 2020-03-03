#include "Vector.hpp"

Vector::Vector(){}

Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(float f)
{
    this->x = f;
    this->y = f;
    this->z = f;
}

Vector Vector::operator*(std::vector<Vector> const &rhs)
{
    Vector res(0);
    res.x = this->x *rhs[0].x + this->y *rhs[0].y + this->z *rhs[0].z;
    res.y = this->x *rhs[1].x + this->y *rhs[1].y + this->z *rhs[1].z;
    res.z = this->x *rhs[2].x + this->y *rhs[2].y + this->z *rhs[2].z;
    return res;
}

Vector Vector::adjust()
{
    this->x = std::clamp(this->x, 0.f, 255.f);
    this->y = std::clamp(this->y, 0.f, 255.f);
    this->z = std::clamp(this->z, 0.f, 255.f);
    return *this;
}

Vector Vector::operator+(Vector const &rhs)
{
    return Vector(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

Vector& Vector::operator+=(Vector const &rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector Vector::operator-(Vector const &rhs)
{
    return Vector(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

float Vector::dot_product(Vector const &rhs)
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector Vector::cross_product(Vector const &rhs)
{
    return Vector(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

float Vector::norm()
{
    return sqrt(this->dot_product(*this));
}

Vector Vector::normalize()
{
    return (*this)*(1/norm());
}

float Vector::get_x()
{
    return x;
}

float Vector::get_y()
{
    return y;
}

void Vector::set_y(float y)
{
    this->y = y;
}

float Vector::get_z()
{
    return z;
}

Vector::~Vector(){}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
Vector operator*(float scalar, Vector const& rhs)
{
    return Vector(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z);
}

Vector operator*(Vector const& lhs, float scalar)
{
    return Vector(scalar * lhs.x, scalar * lhs.y, scalar * lhs.z);
}

Vector operator/(Vector const& lhs, float scalar)
{
    return Vector(lhs.x / scalar, lhs.y / scalar, lhs.z / scalar);
}