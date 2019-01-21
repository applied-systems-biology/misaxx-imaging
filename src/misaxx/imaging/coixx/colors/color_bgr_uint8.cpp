//
// Created by ruman on 17.12.18.
//

#include <misaxx/imaging/coixx/colors/color_bgr_uint8.h>

using namespace coixx;

const color_bgr_uint8 color_bgr_uint8::default_value = color_bgr_uint8(0, 0, 0);
const color_bgr_uint8 color_bgr_uint8::first_value = color_bgr_uint8(0, 0, 0);
const color_bgr_uint8 color_bgr_uint8::last_value = color_bgr_uint8(255, 255, 255);

bool color_bgr_uint8::is_value(const color_bgr_uint8 &) {
    return true;
}

color_bgr_uint8 color_bgr_uint8::black() {
    return color_bgr_uint8(first_value);
}

color_bgr_uint8 color_bgr_uint8::white() {
    return color_bgr_uint8(last_value);
}

color_bgr_uint8::color_bgr_uint8(uchar r, uchar g, uchar b) : pixel_value<uchar, 3>(cv::Vec3b(r, g, b)) {
}

color_bgr_uint8::color_bgr_uint8(const std::string &t_hex) {

    if(t_hex.length() != 7 || t_hex[0] != '#') {
        throw std::runtime_error("String must have format #RRGGBB!");
    }

    unsigned long x = std::stoul(t_hex.substr(1), nullptr, 16);

    unsigned long b = ((x >> 0) & 0xFF);
    unsigned long g = ((x >> 8) & 0xFF);
    unsigned long r = ((x >> 16) & 0xFF);

    get_b() = static_cast<uchar>(b);
    get_g() = static_cast<uchar>(g);
    get_r() = static_cast<uchar>(r);
}

std::string color_bgr_uint8::as_hex() const {
    unsigned int x = ((static_cast<unsigned int>(get_r()) * 255) << 16) |
                     ((static_cast<unsigned int>(get_g()) * 255) << 8) |
                     ((static_cast<unsigned int>(get_b()) * 255) << 0);

    std::stringstream stream;
    stream << "#" << std::setfill('0') << std::setw(6) << std::hex << x;
    std::string result( stream.str() );

    return result;
}

const uchar &color_bgr_uint8::get_r() const {
    return (*this)[2];
}

const uchar &color_bgr_uint8::get_g() const {
    return (*this)[1];
}

const uchar &color_bgr_uint8::get_b() const {
    return (*this)[0];
}

uchar &color_bgr_uint8::get_r() {
    return (*this)[2];
}

uchar &color_bgr_uint8::get_g() {
    return (*this)[1];
}

uchar &color_bgr_uint8::get_b() {
    return (*this)[0];
}
