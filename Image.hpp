#pragma once

#include <vector>
#include "Vector.hpp"
#include <iostream>
#include <fstream>

class Image
{
private:
    std::size_t height;
    std::size_t width;
    std::vector<std::vector<Vector>> pixels;

public:
    Image(std::size_t height, std::size_t width);
    std::size_t get_height();
    std::size_t get_width();
    std::vector<std::vector<Vector>> get_pixels();
    void set_pixel(std::size_t i, std::size_t j, Vector v);
    ~Image();
};