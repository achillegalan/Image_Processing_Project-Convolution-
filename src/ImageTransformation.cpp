#include "ImageTransformation.h"

Image DiscreteConvolution(Image& image, const Image& filter) {
    const int image_width = image.getWidth();
    const int image_height = image.getHeight();
    const int filter_width = filter.getWidth();
    const int filter_height = filter.getHeight();

    Image new_image = image;
    for (size_t i = 0; i < image_width; i++) {
        for (size_t j = 0; j < image_height; j++) {
            double r_conv = 0;
            double g_conv = 0;
            double b_conv = 0;
            for (size_t k = 0; k < filter_height; k++) {
                for (size_t m = 0; m < filter_width; m++) {
                    // Here we apply, channel by channel, the discrete formula for spatial convolution
                    // using image and not new_image here for clarity, they are the same since we copied image
                    // in new_image
                    // (all formulas are needed to implement the "minus index" logic in formula
                    // for an array positive indexing, narrowing conversion is wanted)
                    int conv_x = i + static_cast<int>(filter_width/2.0) - k;
                    int conv_y = j + static_cast<int>(filter_height/2.0) - m;

                    // Mirroring
                    if (conv_x < 0) {
                        conv_x = -conv_x;
                    }
                    if (conv_x > image_width - 1) {
                        int diff = conv_x - (image_width - 1);
                        conv_x = (image_width - 1) - diff;
                    }
                    if (conv_y < 0) {
                        conv_y = -conv_y;
                    }
                    if (conv_y > (image_height - 1)) {
                        int diff = conv_y - (image_height - 1);
                        conv_y = (image_height - 1) - diff;
                    }

                    r_conv += (filter(k, m).r * image(conv_x, conv_y).r);
                    b_conv += (filter(k, m).b * image(conv_x, conv_y).b);
                    g_conv += (filter(k, m).g * image(conv_x, conv_y).g);
                }
            }
            new_image(i, j).r = r_conv;
            new_image(i, j).b = b_conv;
            new_image(i, j).g = g_conv;
        }
    }
    return new_image;
};

Image createLaplaceFilter() {
    Image filter(3, 3);

    filter(0, 0).r = filter(0, 0).g = filter(0, 0).b = 0;
    filter(1, 0).r = filter(1, 0).g = filter(1, 0).b = -1;
    filter(2, 0).r = filter(2, 0).g = filter(2, 0).b = 0;

    filter(0, 1).r = filter(0, 1).g = filter(0, 1).b = -1;
    filter(1, 1).r = filter(1, 1).g = filter(1, 1).b = 4;
    filter(2, 1).r = filter(2, 1).g = filter(2, 1).b = -1;

    filter(0, 2).r = filter(0, 2).g = filter(0, 2).b = 0;
    filter(1, 2).r = filter(1, 2).g = filter(1, 2).b = -1;
    filter(2, 2).r = filter(2, 2).g = filter(2, 2).b = 0;

    return filter;
}