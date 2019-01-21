//
// Created by ruman on 17.12.18.
//

#include <misaxx/imaging/coixx/colors/color_hsv_uint8.h>

using namespace coixx;

const color_hsv_uint8 color_hsv_uint8::default_value = color_hsv_uint8(cv::Vec3b(0, 0, 0));
const color_hsv_uint8 color_hsv_uint8::first_value = color_hsv_uint8(cv::Vec3b(0, 0, 0));
const color_hsv_uint8 color_hsv_uint8::last_value = color_hsv_uint8(cv::Vec3b(179, 255, 255));

bool color_hsv_uint8::is_value(const color_hsv_uint8 &value) {
    return value.get_h() <= 179;
}

color_hsv_uint8 color_hsv_uint8::black() {
    return color_hsv_uint8(first_value);
}

color_hsv_uint8 color_hsv_uint8::white() {
    return color_hsv_uint8(last_value);
}

color_hsv_uint8 color_hsv_uint8::from_double(double h, double s, double v) {
    return color_hsv_uint8(cv::Vec3b(static_cast<uchar>(h * 179), static_cast<uchar>(s * 255), static_cast<uchar>(v * 255)));
}

const uchar &color_hsv_uint8::get_v() const {
    return (*this)[2];
}

const uchar &color_hsv_uint8::get_s() const {
    return (*this)[1];
}

const uchar &color_hsv_uint8::get_h() const {
    return (*this)[0];
}

uchar &color_hsv_uint8::get_v() {
    return (*this)[2];
}

uchar &color_hsv_uint8::get_s() {
    return (*this)[1];
}

uchar &color_hsv_uint8::get_h() {
    return (*this)[0];
}

double color_hsv_uint8::get_v_double() const {
    return get_v() / 255.0;
}

double color_hsv_uint8::get_s_double() const {
    return get_s() / 255.0;
}

double color_hsv_uint8::get_h_double() const {
    return get_h() / 179.0;
}

