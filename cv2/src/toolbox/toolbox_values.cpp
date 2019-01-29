//
// Created by rgerst on 29.01.19.
//

#include <misaxx/imaging/utils/cv2/toolbox/toolbox_values.h>

#include "misaxx/imaging/utils/cv2/toolbox/toolbox_values.h"

namespace {
    template<typename T> void clamp_impl(cv::images::generic &img, double from, double to) {
        const auto min = static_cast<T>(from);
        const auto max = static_cast<T>(to);
        for(int y = 0; y < img.rows; ++y) {
            T *row = img.ptr<T>(y);
            for(int x = 0; x < img.cols; ++x) {
                if(row[x] < min)
                    row[x] = min;
                else if(row[x] > max)
                    row[x] = max;
            }
        }
    }

    template<typename T> void clamp_below_impl(cv::images::generic &img, double from) {
        const auto min = static_cast<T>(from);
        for(int y = 0; y < img.rows; ++y) {
            T *row = img.ptr<T>(y);
            for(int x = 0; x < img.cols; ++x) {
                if(row[x] < min)
                    row[x] = min;
            }
        }
    }

    template<typename T> void clamp_above_impl(cv::images::generic &img, double to) {
        const auto max = static_cast<T>(to);
        for(int y = 0; y < img.rows; ++y) {
            T *row = img.ptr<T>(y);
            for(int x = 0; x < img.cols; ++x) {
                if(row[x] > max)
                    row[x] = max;
            }
        }
    }
}

void cv::toolbox::clamp(cv::images::generic &img, double from, double to) {
    switch(img.type()) {
        case CV_8U:
            return clamp_impl<uchar>(img, from, to);
        case CV_8S:
            return clamp_impl<schar>(img, from, to);
        case CV_16U:
            return clamp_impl<ushort>(img, from, to);
        case CV_16S:
            return clamp_impl<short>(img, from, to);
        case CV_32S:
            return clamp_impl<int>(img, from, to);
        case CV_32F:
            return clamp_impl<float>(img, from, to);
        case CV_64F:
            return clamp_impl<double>(img, from, to);
        default:
            throw std::runtime_error("Unsupported image type!");
    }
}

void cv::toolbox::clamp_below(cv::images::generic &img, double from) {
    switch(img.type()) {
        case CV_8U:
            return clamp_below_impl<uchar>(img, from);
        case CV_8S:
            return clamp_below_impl<schar>(img, from);
        case CV_16U:
            return clamp_below_impl<ushort>(img, from);
        case CV_16S:
            return clamp_below_impl<short>(img, from);
        case CV_32S:
            return clamp_below_impl<int>(img, from);
        case CV_32F:
            return clamp_below_impl<float>(img, from);
        case CV_64F:
            return clamp_below_impl<double>(img, from);
        default:
            throw std::runtime_error("Unsupported image type!");
    }
}

void cv::toolbox::clamp_above(cv::images::generic &img, double to) {
    switch(img.type()) {
        case CV_8U:
            return clamp_above_impl<uchar>(img, to);
        case CV_8S:
            return clamp_above_impl<schar>(img, to);
        case CV_16U:
            return clamp_above_impl<ushort>(img, to);
        case CV_16S:
            return clamp_above_impl<short>(img, to);
        case CV_32S:
            return clamp_above_impl<int>(img, to);
        case CV_32F:
            return clamp_above_impl<float>(img, to);
        case CV_64F:
            return clamp_above_impl<double>(img, to);
        default:
            throw std::runtime_error("Unsupported image type!");
    }
}
