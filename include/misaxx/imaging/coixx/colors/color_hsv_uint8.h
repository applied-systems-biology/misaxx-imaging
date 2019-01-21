//
// Created by rgerst on 07.02.18.
//


#pragma once

#include <misaxx/imaging/coixx/pixel_value.h>

namespace coixx {
    /**
     * Represents an 8-bit HSV color
     */
    class color_hsv_uint8 : public pixel_value<uchar, 3> {

    public:

        using pixel_value<uchar, 3>::pixel_value;

        static const color_hsv_uint8 first_value;
        static const color_hsv_uint8 default_value;
        static const color_hsv_uint8 last_value;

        static bool is_value(const color_hsv_uint8 &value);

        static color_hsv_uint8 black();

        static color_hsv_uint8 white();

        static color_hsv_uint8 from_double(double h, double s, double v);

        const uchar &get_v() const;

        const uchar &get_s() const;

        const uchar &get_h() const;

        uchar &get_v();

        uchar &get_s();

        uchar &get_h();

        double get_v_double() const;

        double get_s_double() const;

        double get_h_double() const;
    };

    namespace colors {
        using hsv8u = color_hsv_uint8;
    }
}