//
// Created by rgerst on 25.01.19.
//

#include <misaxx/imaging/utils/cv2/toolbox/toolbox_semantic_convert.h>
#include <limits>
#include <opencv2/opencv.hpp>

namespace {
    template<typename T> bool is_dynamic_type(const cv::images::buffered &img) {
        return dynamic_cast<const T*>(&img) != nullptr;
    }

    double greyscale_to_percentage(const cv::images::grayscale &img) {
        using namespace cv;
        if(is_dynamic_type<cv::images::grayscale8u >(img)) {
            return 1.0 / std::numeric_limits<uchar>::max();
        }
        else if(is_dynamic_type<cv::images::grayscale8s >(img)) {
            return 1.0 / std::numeric_limits<char>::max();
        }
        else if(is_dynamic_type<cv::images::grayscale16u >(img)) {
            return 1.0 / std::numeric_limits<ushort>::max();
        }
        else if(is_dynamic_type<cv::images::grayscale16s >(img)) {
            return 1.0 / std::numeric_limits<short>::max();
        }
        else if(is_dynamic_type<cv::images::grayscale_floating >(img)) {
            return 1.0;
        }
        else {
            throw std::runtime_error("Unsupported greyscale value!");
        }
    }
}

cv::images::grayscale8u cv::toolbox::semantic_convert::to_grayscale8u(const cv::images::grayscale &img) {
    if(is_dynamic_type<cv::images::grayscale8u >(img))
        return cv::images::grayscale8u(img);
    cv::images::grayscale8u result {};
    const double factor = greyscale_to_percentage(img) * 1.0 / greyscale_to_percentage(result);
    img.convertTo(result, result.type(), factor);
    return result;
}

cv::images::grayscale8s cv::toolbox::semantic_convert::to_grayscale8s(const cv::images::grayscale &img) {
    if(is_dynamic_type<cv::images::grayscale8s >(img))
        return cv::images::grayscale8s(img);
    cv::images::grayscale8s result {};
    const double factor = greyscale_to_percentage(img) * 1.0 / greyscale_to_percentage(result);
    img.convertTo(result, result.type(), factor);
    return result;
}

cv::images::grayscale16u cv::toolbox::semantic_convert::to_grayscale16u(const cv::images::grayscale &img) {
    if(is_dynamic_type<cv::images::grayscale16u >(img))
        return cv::images::grayscale16u(img);
    cv::images::grayscale16u result {};
    const double factor = greyscale_to_percentage(img) * 1.0 / greyscale_to_percentage(result);
    img.convertTo(result, result.type(), factor);
    return result;
}

cv::images::grayscale16s cv::toolbox::semantic_convert::to_grayscale16s(const cv::images::grayscale &img) {
    if(is_dynamic_type<cv::images::grayscale16s >(img))
        return cv::images::grayscale16s(img);;
    cv::images::grayscale16s result {};
    const double factor = greyscale_to_percentage(img) * 1.0 / greyscale_to_percentage(result);
    img.convertTo(result, result.type(), factor);
    return result;
}

cv::images::grayscale32f cv::toolbox::semantic_convert::to_grayscale32f(const cv::images::grayscale &img) {
    if(is_dynamic_type<cv::images::grayscale32f >(img))
        return cv::images::grayscale32f(img);
    cv::images::grayscale32f result {};
    const double factor = greyscale_to_percentage(img) * 1.0 / greyscale_to_percentage(result);
    img.convertTo(result, result.type(), factor);
    return result;
}

cv::images::grayscale64f cv::toolbox::semantic_convert::to_grayscale64f(const cv::images::grayscale &img) {
    if(is_dynamic_type<cv::images::grayscale64f >(img))
        return cv::images::grayscale64f(img);
    cv::images::grayscale64f result {};
    const double factor = greyscale_to_percentage(img) * 1.0 / greyscale_to_percentage(result);
    img.convertTo(result, result.type(), factor);
    return result;
}
