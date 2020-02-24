#include "Image.hpp"

Image::Image(std::size_t height, std::size_t width): height(height), width(width)
{
    pixels = std::vector<std::vector<Vector>> (height, std::vector<Vector>(width, 0));
}

std::vector<std::vector<Vector>> Image::get_pixels()
{
    return pixels;
}

std::size_t Image::get_height()
{
    return height;
}

std::size_t Image::get_width()
{
    return width;
}

void Image::set_pixel(std::size_t i, std::size_t j, Vector v)
{
    pixels[i][j] = v;
}



Image::~Image()
{
}