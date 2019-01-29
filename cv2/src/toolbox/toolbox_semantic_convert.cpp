//
// Created by rgerst on 25.01.19.
//

#include <misaxx/imaging/utils/cv2/toolbox/toolbox_semantic_convert.h>
#include <limits>
#include <opencv2/opencv.hpp>

namespace {
    double greyscale_to_percentage(const cv::images::generic &img) {
        using namespace cv;
        switch(img.type()) {
            case CV_8U:
                return 1.0 / std::numeric_limits<uchar>::max();
            case CV_8S:
                return 1.0 / std::numeric_limits<schar>::max();
            case CV_16U:
                return 1.0 / std::numeric_limits<ushort>::max();
            case CV_16S:
                return 1.0 / std::numeric_limits<short>::max();
            case CV_32F:
            case CV_64F:
                return 1;
            default:
                throw std::runtime_error("Unsupported greyscale value!");
        }
    }
}

cv::images::grayscale8u cv::toolbox::semantic_convert::to_grayscale8u(const cv::images::generic &img) {
    if(img.type() == CV_8U)
        return cv::images::grayscale8u(img.clone());
    cv::images::grayscale8u result {};
    const double factor = greyscale_to_percentage(img) * 1.0 / greyscale_to_percentage(result);
    img.convertTo(result, CV_8U, factor);
    return result;
}

cv::images::grayscale16u cv::toolbox::semantic_convert::to_grayscale16u(const cv::images::generic &img) {
    if(img.type() == CV_16U)
        return cv::images::grayscale16u(img.clone());
    cv::images::grayscale16u result {};
    const double factor = greyscale_to_percentage(img) * 1.0 / greyscale_to_percentage(result);
    img.convertTo(result, CV_16U, factor);
    return result;
}

cv::images::grayscale16s cv::toolbox::semantic_convert::to_grayscale16s(const cv::images::generic &img) {
    if(img.type() == CV_16S)
        return cv::images::grayscale16s(img.clone());
    cv::images::grayscale16s result {};
    const double factor = greyscale_to_percentage(img) * 1.0 / greyscale_to_percentage(result);
    img.convertTo(result, CV_16S, factor);
    return result;
}

cv::images::grayscale32f cv::toolbox::semantic_convert::to_grayscale32f(const cv::images::generic &img) {
    if(img.type() == CV_32F)
        return cv::images::grayscale32f(img.clone());
    cv::images::grayscale32f result {};
    const double factor = greyscale_to_percentage(img) * 1.0 / greyscale_to_percentage(result);
    img.convertTo(result, CV_32F, factor);
    return result;
}

cv::images::grayscale64f cv::toolbox::semantic_convert::to_grayscale64f(const cv::images::generic &img) {
    if(img.type() == CV_64F)
        return cv::images::grayscale64f(img.clone());
    cv::images::grayscale64f result {};
    const double factor = greyscale_to_percentage(img) * 1.0 / greyscale_to_percentage(result);
    img.convertTo(result, CV_64F, factor);
    return result;
}
