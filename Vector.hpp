#pragma once

#include <cmath>
#include <iostream>
#include "Color.hpp"

class Vector
{
private:
    float x;
    float y;
    float z;

public:
    Vector();
    Vector(float x, float y, float z);
    Vector(float f);
    Vector(Vector const &v);
    float magnitude();
    Vector unit_vector();
    Vector operator+(Vector const &rhs);
    Vector operator-(Vector const &rhs);
    Vector operator*(float scalar);
    float dot_product(Vector const &rhs);
    Vector cross_product(Vector const &rhs);
    float norm();
    Vector normalize();
    float get_x();
    float get_y();
    float get_z();
    ~Vector();
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};


