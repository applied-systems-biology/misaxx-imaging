//
// Created by rgerst on 28.01.19.
//

#include <misaxx/imaging/utils/cv2/toolbox/toolbox_normalize.h>

#include "misaxx/imaging/utils/cv2/toolbox/toolbox_normalize.h"
#include <misaxx/imaging/utils/cv2/toolbox/toolbox_normalize.h>
#include <misaxx/imaging/utils/cv2/toolbox/toolbox_statistics.h>

namespace {
    template<typename T> void by_min_max_impl(cv::images::generic &img) {
        const auto min_max = cv::toolbox::statistics::min_max_loc(img);
        const double dmin = min_max.min.value;
        const double dmax = min_max.max.value;
        const double max_supported = std::numeric_limits<T>::max();
        const double min_supported = std::numeric_limits<T>::lowest();
        for(int y = 0; y < img.rows; ++y) {
            auto *row = img.ptr<T>(y);
            for(int x = 0; x < img.cols; ++x) {
                row[x] = static_cast<T>(std::clamp((row[x] - dmin) / (dmax - dmin) * max_supported, min_supported, max_supported));
            }
        }
    }
}

void cv::toolbox::normalize::by_max(cv::images::generic &img) {
    double max = cv::toolbox::statistics::min_max_loc(img).max.value;
    img /= max;
}

void cv::toolbox::normalize::by_min_max(cv::images::generic &img) {
    switch(img.type()) {
        case CV_8U:
            return by_min_max_impl<uchar>(img);
        case CV_8S:
            return by_min_max_impl<schar>(img);
        case CV_16U:
            return by_min_max_impl<ushort>(img);
        case CV_16S:
            return by_min_max_impl<short>(img);
        case CV_32S:
            return by_min_max_impl<int>(img);
        case CV_32F:
            return by_min_max_impl<float>(img);
        case CV_64F:
            return by_min_max_impl<double>(img);
        default:
            throw std::runtime_error("Unsupported image type!");
    }
}
