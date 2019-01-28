//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/static_types.h>
#include <misaxx/imaging/utils/cv2/pixel.h>

/**
 * General query functions
 */
namespace cv::toolbox {

    struct min_max_result {
        pixel<double> min;
        pixel<double> max;
    };
}

namespace cv::toolbox::statistics {

    extern min_max_result min_max_loc(const images::grayscale &img);

    extern std::unordered_map<double, double> get_percentiles(const images::grayscale &img, const std::vector<double> &percentiles);

    extern double get_percentile(const images::grayscale &img, double percentile);
}


