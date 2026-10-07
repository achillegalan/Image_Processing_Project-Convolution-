#include "ImageTransformation.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "1. Loading image...\n";
    Image image = loadImageFromFile("rocco.jpg");
    std::cout << "2. Image loaded: "
              << image.getWidth() << " x "
              << image.getHeight() << '\n';

    std::cout << "Applying Filters...\n";
    GammaCorrector gamma;
    GrayScaler gray;
    LaplaceFilter laplace_filter;
    std::vector<ImageTransformation*> filters{&gamma, &gray, &laplace_filter};
    std::vector<std::string> names = {"gamma","grayscale","laplace"};

    int i = 0;
    for (ImageTransformation* filter : filters) {
        Image filtered_image = filter->apply(image);
        saveImageAsJpeg(filtered_image, names[i]+"_rocco.jpg");
        i += 1;
    };

    std::cout << "Transformations Done and Saved!\n";

    return 0;
}