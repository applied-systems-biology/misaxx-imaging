//
// Created by rgerst on 25.01.19.
//

#include <misaxx/imaging/utils/cv2/toolbox/toolbox_binarize.h>

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
