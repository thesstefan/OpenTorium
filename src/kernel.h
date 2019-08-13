#pragma once

#include <stdexcept>
#include <iostream>

#include <array>
#include <type_traits>

#include "gauss_distribution.h"

template <typename Type, size_t width, size_t height,
    typename std::enable_if<std::is_floating_point<Type>::value, Type>::type* = nullptr
>
/** @brief Small matrix used for image processing. **/
class Kernel {
    private:
        /** @brief The values of the Kernel. **/
        std::array<std::array<Type, width>, height> kernelData;

    public:
        /** 
         * @brief Constructs the Kernel. 
         *
         * @warning The input matrix must not be empty, have even dimensions, or
         *          different row-dimensions. Otherwise, std::invalid_argument 
         *          is thrown.
         */
        Kernel(const std::array<std::array<Type, width>, height>& kernelData) {
            if (height % 2 == 0 || width % 2 == 0)
                throw std::invalid_argument("std::invalid_argument:"
                        "Kernel::Kernel() -> matrix must have odd dimensions.");

            this->kernelData = kernelData;
        }

        /** @brief Copy-construct the Kernel. **/
        Kernel(const Kernel& kernel) {;
            this->kernelData = kernel.data();
        }

        /** @brief Returns the internal data of the Kernel. **/
        std::array<std::array<Type, width>, height> data() const {
            return kernelData;
        }

        /** 
         * @brief Normalizes the Kernel values. 
         *
         * @returns The factor used for the normalization.
         */
        Type normalize() {
            Type sum = 0;
            for (const auto &row : kernelData)
                for (const auto &element : row)
                    sum += element;

            const Type multiplier = 1 / sum;
            for (auto &row : kernelData)
                for (auto &element : row)
                    element *= multiplier;

            return multiplier;
        }

        /** 
         * @brief Returns the specified row of the Kernel. 
         *
         * @warning If index > height, std::out_of_bounds is thrown. 
         * **/
        std::array<Type, width> operator[](const size_t index) const {
            return kernelData.at(index);
        }
        
        /** @brief Returns the height of the Kernel. **/
        size_t getHeight() const { return height; }
        
        /** @brief Returns the width of the Kernel. **/
        size_t getWidth() const { return width; }
};

template <typename Type, size_t width, size_t height,
    typename std::enable_if<std::is_floating_point<Type>::value, Type>::type* = nullptr
>

/**
* @brief Extracts the necessary data from a normal distribution with 
*        mean 0 and a given variance to create a Kernel.
*
* @param variance -> The variance of the distribution used to create
*                    the Kernel.
*
* @warning The variance must be positive. 
*          std::invalid_argument is thrown otherwise.
*/
std::array<std::array<Type, width>, height> 
    getGaussianData(const double variance) {

    if (width % 2 == 0 || height % 2 == 0)
        throw std::invalid_argument("std::invalid_argument:"
                "getGaussianData() -> kernel must have odd dimensions.");

    const size_t centerX = width / 2;
    const size_t centerY = height / 2;

    std::array<std::array<Type, width>, height> kernelData;

    for (size_t heightIndex = 0; heightIndex < height; heightIndex++) {
        std::array<Type, width> kernelRow;

        for (size_t widthIndex = 0; widthIndex < width; widthIndex++) {
            int widthDist = widthIndex - centerX;
            int heightDist = heightIndex - centerY;

            const Type probability = 
                gaussianProbabilty(std::abs(widthDist), 0, variance) *
                gaussianProbabilty(std::abs(heightDist), 0, variance);

            kernelRow[widthIndex] = probability;
        }

        kernelData[heightIndex] = kernelRow;
    }

    return kernelData;
}

template <typename Type, size_t width, size_t height,
    typename std::enable_if<std::is_floating_point<Type>::value, Type>::type* = nullptr
>
/** Kernel created using a gaussian distribution. Used to blur. **/
class GaussianKernel : public Kernel<Type, width, height> {
    public:
        /**
         * @brief Creates a kernel from a normal distribution 
         *        with mean 0 and a given variance.
         *
         * Calls getGaussianData(). All requirements apply.
         */
        GaussianKernel(const double variance) : 
            Kernel<Type, width, height>(getGaussianData<Type, width, height>(variance)) {}
};
