#pragma once

#include "ofImage.h"
#include "kernel.h"

template <typename InputType, typename OutputType>
ofImage_<OutputType> convert(const ofImage_<InputType> &input) {
    const ofPixels_<InputType> pixels = input.getPixels();

    ofPixels_<OutputType> output;
    output.allocate(pixels.getWidth(), pixels.getHeight(),
                    OF_PIXELS_RGB);

    for (size_t row = 0; row < pixels.getHeight(); row++)
        for (size_t col = 0; col < pixels.getWidth(); col++) {
            ofColor_<InputType> color = input.getColor(col, row);

            output.setColor(col, row, 
                            ofColor(static_cast<OutputType>(color.r), 
                                    static_cast<OutputType>(color.g), 
                                    static_cast<OutputType>(color.b)));
        }

    ofImage_<OutputType> outputImg;
    outputImg.setFromPixels(output.getData(), 
                            output.getWidth(), 
                            output.getHeight(), 
                            OF_IMAGE_COLOR);
                
    return outputImg;
}

// Handles convolution at the margins of the image. (mirroring)
size_t borderHandling(const int coordinate, 
                      const int max) {
    if (coordinate < max && coordinate >= 0)
        return coordinate;

    if (coordinate < 0)
        return max + coordinate;

    return coordinate % max;
}

template <typename InputType, typename OutputType,
          typename kType, size_t kWidth, size_t kHeight>
ofImage_<OutputType> convolve_(const ofImage_<InputType> &input, 
                               const Kernel<kType, kWidth, kHeight> &kernel) {
    const ofPixels_<InputType> pixels = input.getPixels();

    ofPixels_<OutputType> output;
    output.allocate(pixels.getWidth(), pixels.getHeight(),
                    OF_PIXELS_RGB);

    for (size_t row = 0; row < pixels.getHeight(); row++)
        for (size_t col = 0; col < pixels.getWidth(); col++) {
            float red = 0;
            float green = 0;
            float blue = 0;

            // Avoid size_t -> int conversions
            const int rowBound = kHeight / 2;
            const int colBound = kWidth / 2;

            for (int kernelRow = -rowBound; 
                     kernelRow <= rowBound; 
                     kernelRow++)

                for (int kernelCol = -colBound;
                         kernelCol <= colBound;
                         kernelCol++) {

                    const size_t usedRow = 
                        borderHandling(row + kernelRow, pixels.getHeight());
                    const size_t usedCol = 
                        borderHandling(col + kernelCol, pixels.getWidth());

                    const double multiplier = kernel[kernelRow + rowBound]
                                                    [kernelCol + colBound];

                    const ofColor_<InputType> color = pixels.getColor(usedCol, usedRow);

                    red   += static_cast<OutputType>(color.r) * multiplier;
                    green += static_cast<OutputType>(color.g) * multiplier;
                    blue  += static_cast<OutputType>(color.b) * multiplier;
                }

            output.setColor(col, row, ofColor_<OutputType>(red, green, blue, 255));
        }
    
    ofImage_<OutputType> outputImg;
    outputImg.setFromPixels(output.getData(), 
                            output.getWidth(), 
                            output.getHeight(), 
                            OF_IMAGE_COLOR);

    return outputImg;
}

template <typename InputType, typename OutputType,
          typename kType, size_t kWidth, size_t kHeight>
ofImage_<OutputType> iterativeConvolve_(const ofImage_<InputType> &image, 
                                        const Kernel<kType, kWidth, kHeight> &kernel,
                                        const int times) {
    ofFloatImage result = 
        convolve_<InputType, float, kType, kWidth, kHeight>(image, kernel);

    for (int index = 1; index < times; index++)
        result = convolve_<float, float, kType, kWidth, kHeight>
            (result, kernel);

    return convert<float, OutputType>(result);
}

/** 
 * @brief Converts an ofFloatImage to an ofImage.
 *
 * @warning Accuracy can be lost as float to unsigned char
 *          conversions are made.
 */
ofImage convertToImage(const ofFloatImage &input) {
    return convert<float, unsigned char>(input);
}

/**
 * @brief Convolve an ofImage with a Kernel using float values.
 *
 * This is more accuarate than convolve and it's recommended to
 * be used while dealing with successive convolutions.
 */
template <typename kType, size_t kWidth, size_t kHeight>
ofFloatImage float_convolve(const ofImage &input,
                            const Kernel<kType, kWidth, kHeight> &kernel) {
    return convolve_<unsigned char, float, kType, kWidth, kHeight>
        (input, kernel);
}

/**
 * @brief Convolves an ofImage with a Kernel using unsigned char values. 
 *
 * For succesive calls, iterativeConvolve is recommended for
 * better accuracy.
 */
template <typename kType, size_t kWidth, size_t kHeight>
ofImage convolve(const ofImage &input, 
                 const Kernel<kType, kWidth, kHeight> &kernel) {
    return convolve_<unsigned char, unsigned char, kType, kWidth, kHeight>
        (input, kernel);
}

/**
 * @brief Applies convolution operations iteratively on an image. 
 *
 * Accuracy is manitained by using float_convolve.
 *
 * @param input -> The image to be used.
 * @param kernel -> The kernel to be used.
 * @param times -> The number of convolve operations to be applied.
 */
template <typename kType, size_t kWidth, size_t kHeight>
ofImage iterativeConvolve(const ofImage &image, 
                          const Kernel<kType, kWidth, kHeight> &kernel,
                          const int times) {
    return iterativeConvolve_<unsigned char, unsigned char, kType, kWidth, kHeight>
        (image, kernel, times);
}
