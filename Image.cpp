#include "Image.hpp"

Image::Image(std::size_t height, std::size_t width, float fov): height(height), width(width)
{
    pixels = std::vector<std::vector<Vector>> (height, std::vector<Vector>(width, 0));
    float scale = tan(fov * 0.5 * (M_PI / 180)); 
    float imageAspectRatio = width / height; 
    for (std::size_t i = 0; i < height; i++)
    {
        for (std::size_t j = 0; j < width; j++)
        {
            float x = (2 * (i + 0.5) / width - 1) * imageAspectRatio * scale; 
            float y = (1 - 2 * (j + 0.5) / height) * scale;
            Vector v(x, y, -1);
            pixels[i].push_back(v.normalize());
        }
    }
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