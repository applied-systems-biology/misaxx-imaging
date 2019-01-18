//
// Created by ruman on 17.12.18.
//

#include <misaxx-imaging/coixx/structuring_element.h>
#include <misaxx-imaging/coixx/image.h>

coixx::images::mask coixx::structuring_element::get(coixx::structuring_element::type t_type, int t_width, int t_height) {
    return coixx::images::mask(cv::getStructuringElement(static_cast<int>(t_type), cv::Size(t_width, t_height)));
}

coixx::images::mask coixx::structuring_element::rectangle(int t_width, int t_height) {
    return coixx::structuring_element::get(coixx::structuring_element::type::rectangle, t_width, t_height);
}

coixx::images::mask coixx::structuring_element::rectangle(int t_size) {
    return rectangle(t_size, t_size);
}

coixx::images::mask coixx::structuring_element::ellipse(int t_size) {
    return ellipse(t_size, t_size);
}

coixx::images::mask coixx::structuring_element::cross(int t_size) {
    return cross(t_size, t_size);
}

coixx::images::mask coixx::structuring_element::circle_with_hole(int t_size) {
    if(t_size % 2 == 0)
        throw std::runtime_error("Circle size must be uneven!");
    auto result = ellipse(t_size, t_size);
    result.at(t_size / 2, t_size / 2) = colors::mask::background();
    return result;
}

coixx::images::mask coixx::structuring_element::circle(int t_size) {
    return ellipse(t_size);
}

coixx::images::mask coixx::structuring_element::cross(int t_width, int t_height) {
    return structuring_element::get(type::cross, t_width, t_height);
}

coixx::images::mask coixx::structuring_element::ellipse(int t_width, int t_height) {
    return structuring_element::get(type::ellipse, t_width, t_height);
}

coixx::images::mask coixx::structuring_element::square(int t_size) {
    return rectangle(t_size);
}
