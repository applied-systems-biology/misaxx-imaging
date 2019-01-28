//
// Created by rgerst on 28.01.19.
//

#include "misaxx/imaging/utils/cv2/structuring_element.h"

cv::images::mask cv::structuring_element::get(cv::structuring_element_type t_type, int t_width, int t_height) {
    return cv::images::mask(cv::getStructuringElement(static_cast<int>(t_type), cv::Size(t_width, t_height)));
}

cv::images::mask cv::structuring_element::rectangle(int t_width, int t_height) {
    return cv::structuring_element::get(cv::structuring_element_type::rectangle, t_width, t_height);
}

cv::images::mask cv::structuring_element::rectangle(int t_size) {
    return rectangle(t_size, t_size);
}

cv::images::mask cv::structuring_element::ellipse(int t_size) {
    return ellipse(t_size, t_size);
}

cv::images::mask cv::structuring_element::cross(int t_size) {
    return cross(t_size, t_size);
}

cv::images::mask cv::structuring_element::circle_with_hole(int t_size) {
    if(t_size % 2 == 0)
        throw std::runtime_error("Circle size must be uneven!");
    auto result = ellipse(t_size, t_size);
    result.at<uchar>(t_size / 2, t_size / 2) = 0;
    return result;
}

cv::images::mask cv::structuring_element::circle(int t_size) {
    return ellipse(t_size);
}

cv::images::mask cv::structuring_element::cross(int t_width, int t_height) {
    return structuring_element::get(structuring_element_type::cross, t_width, t_height);
}

cv::images::mask cv::structuring_element::ellipse(int t_width, int t_height) {
    return structuring_element::get(structuring_element_type::ellipse, t_width, t_height);
}

cv::images::mask cv::structuring_element::square(int t_size) {
    return rectangle(t_size);
}
