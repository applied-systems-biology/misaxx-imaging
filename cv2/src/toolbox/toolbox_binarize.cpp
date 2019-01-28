//
// Created by rgerst on 25.01.19.
//

#include <misaxx/imaging/utils/cv2/toolbox/toolbox_binarize.h>

namespace {
    template<typename T> cv::images::mask to_mask_impl(const cv::images::generic &img) {
        cv::images::mask result { cv::images::mask::allocate(img.size(), CV_8U) };
        cv::G_8U_BMat(cv::BMat());
        for(int y = 0; y < img.rows; ++y) {
            const T *src_row = img.ptr<T>(y);
            auto *dst_row = result.static_ptr(y);
            for(int x = 0; x < img.cols; ++x) {
                if(src_row[x] > 0) {
                    dst_row[x] = 255;
                }
                else {
                    dst_row[x] = 0;
                }
            }
        }
    }
}

void cv::toolbox::binarize(cv::images::grayscale8u &img, uchar threshold, uchar signal_value, bool invert) {
    if(!invert)
        cv::threshold(img, img.buffer(true), threshold, signal_value, cv::THRESH_BINARY);
    else
        cv::threshold(img, img.buffer(true), threshold, signal_value, cv::THRESH_BINARY_INV);
    img.swap();
}

void cv::toolbox::binarize(cv::images::grayscale32f &img, float threshold, float signal_value, bool invert) {
    if(!invert)
        cv::threshold(img, img.buffer(true), threshold, signal_value, cv::THRESH_BINARY);
    else
        cv::threshold(img, img.buffer(true), threshold, signal_value, cv::THRESH_BINARY_INV);
    img.swap();
}

cv::images::mask cv::toolbox::to_mask(const cv::images::grayscale32s &img) {
    return cv::images::mask();
}
