#ifndef ASS2_IMAGETRANSFORMATION_H
#define ASS2_IMAGETRANSFORMATION_H
#include <iostream>

#include "image.hpp"

Image DiscreteConvolution(Image& image, const Image& filter);
Image createLaplaceFilter();

class ImageTransformation {
private:

public:
    inline ImageTransformation() = default;
    inline virtual ~ImageTransformation() = default;

    inline virtual Image apply(Image& image) = 0;
};

class GammaCorrector: public ImageTransformation {
private:

public:
    inline GammaCorrector() = default;
    inline ~GammaCorrector() override = default;

    inline Image apply(Image& image) override {
        double gamma = 0;

        do {
            std::cout << "Insert Gamma Value: ";
            std::cin >> gamma;
            if (gamma <= 0) {
                std::cout << "Gamma must be positive. Try again.\n";
            }
        } while (gamma <= 0);

        return GammaCorrection(image, gamma);
    }
};

class GrayScaler: public ImageTransformation {
private:

public:
    inline GrayScaler() = default;
    ~GrayScaler() override = default;

    inline Image apply(Image& image) override {
        return GrayScale(image);
    }

};

class SpatialConvolution: public ImageTransformation {
protected:
    Image filter;

public:
    SpatialConvolution(const Image& kernel): filter(kernel) {};
    inline ~SpatialConvolution() override = default;

    inline Image apply(Image& image) override {
        return  DiscreteConvolution(image, filter);
    }

};

class LaplaceFilter: public SpatialConvolution {
public:
    LaplaceFilter() : SpatialConvolution(createLaplaceFilter()){} ;

    inline ~LaplaceFilter() override = default;

    inline Image apply(Image& image) override {
        return  DiscreteConvolution(image, filter);
    }

};

#endif //ASS2_IMAGETRANSFORMATION_H
