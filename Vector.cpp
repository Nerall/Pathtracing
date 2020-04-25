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

Vector& Vector::operator/=(float const &rhs)
{
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}

Vector Vector::operator*(std::vector<Vector> const &rhs)
{
    Vector res(0);
    res.x = this->x *rhs[0].x + this->y *rhs[0].y + this->z *rhs[0].z;
    res.y = this->x *rhs[1].x + this->y *rhs[1].y + this->z *rhs[1].z;
    res.z = this->x *rhs[2].x + this->y *rhs[2].y + this->z *rhs[2].z;
    return res;
}

float Vector:: max_component()
{
    return std::max(this->x, std::max(this->y, this->z));
}

Vector Vector::adjust()
{
    this->x = std::clamp(this->x, 0.f, 1.f);
    this->y = std::clamp(this->y, 0.f, 1.f);
    this->z = std::clamp(this->z, 0.f, 1.f);
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

Vector operator*(std::vector<Vector> const &lhs, const Vector& rhs)
{
    Vector res(0);
    res.x = lhs[0].x * rhs.x + lhs[1].x * rhs.y + lhs[2].x * rhs.z;
    res.y = lhs[0].y * rhs.x + lhs[1].y * rhs.y + lhs[2].y * rhs.z;
    res.z = lhs[0].z * rhs.x + lhs[1].z * rhs.y + lhs[2].z * rhs.z;
    return res;
}

bool operator==(Vector const &left, float right)
{
    return (left.x == right && left.y == right && left.z == right);
}

Vector& Vector::operator*=(float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

/*Vector operator+(Vector lhs, Vector const& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}*/

Vector operator/(Vector const& lhs, float scalar)
{
    return Vector(lhs.x / scalar, lhs.y / scalar, lhs.z / scalar);
}