//
// Created by rgerst on 28.01.19.
//

#pragma once

#include <opencv2/imgproc.hpp>

namespace cv::toolbox {

    /**
     * Available resize interpolations
     */
    enum resize_interpolation : int {
        linear = cv::INTER_LINEAR,
        cubic = cv::INTER_CUBIC,
        nearest = cv::INTER_NEAREST
    };

    /**
     * Resizes the input image
     * @tparam _Mat
     * @param img
     * @param size
     * @param interpolation
     * @return
     */
    template<class _Mat> inline _Mat resize(const _Mat &img, const cv::Size &size, resize_interpolation interpolation = resize_interpolation::nearest) {
        _Mat result;
        cv::resize(img, result, size, 0, 0, static_cast<int>(interpolation));
        return result;
    }

    /**
     * Resizes the input image
     * @tparam _Mat
     * @param img
     * @param factor
     * @param interpolation
     * @return
     */
    template<class _Mat> inline _Mat resize(const _Mat &img, double factor, resize_interpolation interpolation = resize_interpolation::nearest) {
        if(factor <= 0) {
            throw std::runtime_error("Unsupported resize factor of " + std::to_string(factor));
        }
        return resize(img, cv::Size(static_cast<int>(img.cols * factor), static_cast<int>(img.rows * factor)), interpolation);
    }

}


