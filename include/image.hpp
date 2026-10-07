// SF2565/FSF3565 Assignment 2 skeleton code (author: Bjorn Wehlin)

#ifndef IMAGE_SKELETON_HPP
#define IMAGE_SKELETON_HPP

#include <string>

struct Pixel
{
  double r, g, b;
};

class Image
{
public:

  inline Image(size_t w, size_t h):  width(w), height(h),  pixels(new Pixel[width * height])
  {};

  Image(const Image& other);

  inline ~Image() {
    delete[] pixels;
  }

  inline Pixel& operator()(size_t x, size_t y) {
    return pixels[y * width + x];
  }

  inline const Pixel& operator()(size_t x, size_t y) const
  {
    return pixels[y * width + x];
  }

  inline int getWidth() const{
    return width;
  }

  inline int getHeight() const {
    return height;
  }

  Image& operator=(const Image& other);

private:
  int width;
  int height;
  Pixel* pixels;
};

Image loadImageFromFile(const std::string& filename);
void saveImageAsJpeg(const Image& image, const std::string& filename);
Image GammaCorrection(Image& image, const double& gamma);
Image GrayScale(Image& image);

#endif // IMAGE_SKELETON_HPP
