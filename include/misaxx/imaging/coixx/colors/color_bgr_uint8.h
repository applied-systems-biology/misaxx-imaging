//
// Created by rgerst on 07.02.18.
//


#pragma once

#include <iomanip>
#include <misaxx/imaging/coixx/pixel_value.h>

namespace coixx {
    /**
 * Represents an 8-bit BGR color
 */
    class color_bgr_uint8 : public pixel_value<uchar, 3> {

    public:

        using pixel_value<uchar, 3>::pixel_value;
        static const color_bgr_uint8 default_value;
        static const color_bgr_uint8 first_value;
        static const color_bgr_uint8 last_value;

        static bool is_value(const color_bgr_uint8 &value);

        static color_bgr_uint8 black();

        static color_bgr_uint8 white();

        /**
         * Loads this color from r, g and b
         * @param r
         * @param g
         * @param b
         */
        explicit color_bgr_uint8(uchar r, uchar g, uchar b);

        /**
         * Loads this color from a hex string #RRGGBB
         * @param t_hex
         */
        explicit color_bgr_uint8(const std::string &t_hex);

        /**
         * Converts into OpenCV vec
         * @return
         */
        inline operator cv::Vec<uchar, 3>() {
            return *this;
        }

        /**
        * Converts the color to a hex string #RRGGBB
        * @return
        */
        std::string as_hex() const;

        const uchar &get_r() const;

        const uchar &get_g() const;

        const uchar &get_b() const;

        uchar &get_r();

        uchar &get_g();

        uchar &get_b();
    };

    namespace colors {
        using bgr8u = color_bgr_uint8;
    }
}