//
// Created by rgerst on 21.11.18.
//


#pragma once

#include <misaxx/imaging/coixx/pixel_value.h>

namespace coixx {
    template<typename ChannelType> struct color_grayscale_floating : public pixel_value<ChannelType, 1> {
        static const color_grayscale_floating<ChannelType> first_value;
        static const color_grayscale_floating<ChannelType> default_value;
        static const color_grayscale_floating<ChannelType> last_value;

        using pixel_value<ChannelType, 1>::pixel_value;

        /**
         * Converts into OpenCV vec
         * @return
         */
        inline operator cv::Vec<ChannelType, 1>() {
            return *this;
        }

        static bool is_value(const pixel_value<ChannelType, 1> &value) {
            return true;
        }

        static color_grayscale_floating<ChannelType> black() {
            return first_value;
        }

        static color_grayscale_floating<ChannelType> white() {
            return last_value;
        }

        bool operator == (const color_grayscale_floating<ChannelType> &t_other) const {
            return static_cast<ChannelType>(*this) == static_cast<ChannelType>(t_other);
        }

        bool operator != (const color_grayscale_floating<ChannelType> &t_other) const {
            return static_cast<ChannelType>(*this) != static_cast<ChannelType>(t_other);
        }

        bool operator < (const color_grayscale_floating<ChannelType> &t_other) const {
            return static_cast<ChannelType>(*this) < static_cast<ChannelType>(t_other);
        }

        bool operator > (const color_grayscale_floating<ChannelType> &t_other) const {
            return static_cast<ChannelType>(*this) > static_cast<ChannelType>(t_other);
        }
    };

    template<typename ChannelType> inline const color_grayscale_floating<ChannelType> color_grayscale_floating<ChannelType>::default_value = color_grayscale_floating<ChannelType>(0);
    template<typename ChannelType> inline const color_grayscale_floating<ChannelType> color_grayscale_floating<ChannelType>::first_value = color_grayscale_floating<ChannelType>(0);
    template<typename ChannelType> inline const color_grayscale_floating<ChannelType> color_grayscale_floating<ChannelType>::last_value = color_grayscale_floating<ChannelType>(1);

    namespace colors {
        using grayscale_float = color_grayscale_floating<float>;
        using grayscale_double = color_grayscale_floating<double>;
        using grayscale32f = color_grayscale_floating<float>;
        using grayscale64f = color_grayscale_floating<double>;
    }
}

namespace std {
    template<typename ChannelType>
    struct hash<coixx::color_grayscale_floating<ChannelType>> {
        size_t operator()(const coixx::color_grayscale_floating<ChannelType> &x) const {
            return hash<typename coixx::color_grayscale_floating<ChannelType>::raw_type>(x)();
        }
    };
}
