// SF2565/FSF3565 Assignment 2 skeleton code (author: Bjorn Wehlin)

#include "image.hpp"
#include <cmath>
#include <iostream>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(const Image& other) {
    width = other.getWidth();
    height = other.getHeight();
    pixels = new Pixel[width * height];

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            pixels[j * width + i] = other(i, j);
        }
    }
}

Image& Image::operator=(const Image& other)
{
    if (this == &other) return *this;

    int new_width = other.getWidth();
    int new_height = other.getHeight();
    auto tempImg = std::make_unique<Pixel[]>(new_width * new_height);
    for (size_t i = 0; i < new_width; i++) {
        for (size_t j = 0; j < new_height; j++) {
            tempImg[j * new_width + i] = other(i, j);
        }
    }
    delete[] pixels;

    pixels = tempImg.release();
    width = new_width;
    height = new_height;

    return *this;
}

Image loadImageFromFile(const std::string& filename)
{
    int width, height;
    int channels = 3;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    if (data == nullptr)
    {
        std::cerr << "ERROR: Could not load image: "
                  << filename << "\n";
        std::cerr << "STB reason: "
                  << stbi_failure_reason() << "\n";

        throw std::runtime_error("Image loading failed");
    }

    std::cout << "Image loaded: "
              << width << " x " << height << "\n";

    Image image(width, height);

// Now we have to fill manually every channel of every pixel, converting from [0, 255] range
// to [0, 1] range
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            const int pixel_index = static_cast<int>(j * width * channels + i * channels);
            image(i, j).r = data[pixel_index]/255.0;
            image(i, j).g = data[pixel_index+1]/255.0;
            image(i, j).b = data[pixel_index+2]/255.0;
        }
    }
    stbi_image_free(data);
    return image;
}

void saveImageAsJpeg(const Image& image, const std::string& filename)
{
    const int width = image.getWidth();
    const int height = image.getHeight();
    const int channels = 3;

    unsigned char* data = new unsigned char[width*height*3];

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            const int pixel_index = static_cast<int>(j * width * channels + i * channels);
            data[pixel_index] = static_cast<unsigned char>(image(i,j).r * 255.0);
            data[pixel_index+1] = static_cast<unsigned char>(image(i,j).g * 255.0);
            data[pixel_index+2] = static_cast<unsigned char>(image(i,j).b * 255.0);
        }
    }

    stbi_write_jpg(filename.c_str(), width, height, 3, data, 90);
    delete[] data;
}

Image GammaCorrection(Image& image, const double &gamma) {

    //Image new_image = image;
    const int width = image.getWidth();
    const int height = image.getHeight();

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            image(i, j).r = std::pow(image(i,j).r, gamma);
            image(i, j).g = std::pow(image(i,j).g, gamma);
            image(i, j).b = std::pow(image(i,j).b, gamma);
        }
    }
    return image;
}

Image GrayScale(Image& image) {

    //Image new_image = image;
    const int width = image.getWidth();
    const int height = image.getHeight();

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            image(i, j).r = 0.2126 * image(i,j).r +
                                    0.7152 * image(i,j).g +
                                    0.0722 * image(i,j).b;

            image(i, j).g = 0.2126 * image(i,j).r +
                                    0.7152 * image(i,j).g +
                                    0.0722 * image(i,j).b;
            image(i, j).b = 0.2126 * image(i,j).r +
                                    0.7152 * image(i,j).g +
                                    0.0722 * image(i,j).b;
        }
    }
    return image;
}
