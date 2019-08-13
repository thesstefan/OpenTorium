#pragma once

#include <stdexcept>

#include "ofImage.h"

#include "kernel.h"
#include "image_convolve.h"

ofImage blend(ofImage &top, ofImage &bottom) {
    for (size_t row = 0; row < top.getHeight(); row++)
        for (size_t col = 0; col < top.getWidth(); col++) {
            ofColor topColor = top.getColor(col, row);

            if (topColor != ofColor(0, 0, 0))
                output.setColor(col, row, topColor);
            else
                output.setColor(col, row, bottom.getColor(col, row));
        }

    ofImage outputImg;
    outputImg.setFromPixels(output.getData(), 
                            output.getWidth(), 
                            output.getHeight(), 
                            OF_IMAGE_COLOR);
                
    return outputImg;
}

/**
 * @brief Applies a glow effect on an image by drawing
 *        the blurred image over the given one.
 *
 * @param image -> The image to be glowing.
 * @param kernel -> The kernel to be used to blur.
 */
template <typename kType, size_t kWidth, size_t kHeight>
ofImage glow(const ofImage &image,
             const Kernel<kType, kWidth, kHeight> &kernel) {
    ofImage blurred;

    blurred = convolve(image, kernel);

    return blend(image, blurred);
}
