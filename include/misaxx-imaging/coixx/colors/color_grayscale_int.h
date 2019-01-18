//
// Created by rgerst on 21.11.18.
//


#pragma once

#include <misaxx-imaging/coixx/pixel_value.h>

namespace coixx {
    template<typename ChannelType>
    struct color_grayscale_int : public pixel_value<ChannelType, 1> {
        static const color_grayscale_int<ChannelType> first_value;
        static const color_grayscale_int<ChannelType> default_value;
        static const color_grayscale_int<ChannelType> last_value;

        using pixel_value<ChannelType, 1>::pixel_value;

        explicit operator double() const {
            return this->value;
        }

        static bool is_value(const pixel_value<ChannelType, 1> &value) {
            return true;
        }

        static void next_value(color_grayscale_int<ChannelType> &value) {
            if (value.value != last_value.value)
                ++value.value;
        }

        static color_grayscale_int<ChannelType> black() {
            return color_grayscale_int<ChannelType>(0);
        }

        static color_grayscale_int<ChannelType> white() {
            return color_grayscale_int<ChannelType>(last_value);
        }

        static color_grayscale_int<ChannelType> foreground() {
            return white();
        }

        static color_grayscale_int<ChannelType> background() {
            return black();
        }

        bool is_background() const {
            return *this == 0;
        }

        bool is_foreground() const {
            return *this > 0;
        }

        bool operator == (const color_grayscale_int<ChannelType> &t_other) const {
            return this->value == t_other.value;
        }

        bool operator != (const color_grayscale_int<ChannelType> &t_other) const {
            return this->value != t_other.value;
        }

        bool operator < (const color_grayscale_int<ChannelType> &t_other) const {
            return this->value < t_other.value;
        }

        bool operator > (const color_grayscale_int<ChannelType> &t_other) const {
            return this->value > t_other.value;
        }

        color_grayscale_int<ChannelType> operator += (const color_grayscale_int<ChannelType> &t_other) {
            this->value += t_other.value;
            return *this;
        }

        friend color_grayscale_int<ChannelType> operator +(color_grayscale_int<ChannelType> lhs, const color_grayscale_int<ChannelType> &rhs) {
            lhs += rhs;
            return lhs;
        }

        color_grayscale_int<ChannelType> operator -= (const color_grayscale_int<ChannelType> &t_other) {
            this->value -= t_other.value;
            return this;
        }

        friend color_grayscale_int<ChannelType> operator -(color_grayscale_int<ChannelType> lhs, const color_grayscale_int<ChannelType> &rhs) {
            lhs += rhs;
            return lhs;
        }

        color_grayscale_int<ChannelType> operator *= (const color_grayscale_int<ChannelType> &t_other) {
            this->value *= t_other.value;
            return *this;
        }

        friend color_grayscale_int<ChannelType> operator *(color_grayscale_int<ChannelType> lhs, const color_grayscale_int<ChannelType> &rhs) {
            lhs *= rhs;
            return lhs;
        }

        color_grayscale_int<ChannelType> operator /= (const color_grayscale_int<ChannelType> &t_other) {
            this->value /= t_other.value;
            return *this;
        }

        friend color_grayscale_int<ChannelType> operator /(color_grayscale_int<ChannelType> lhs, const color_grayscale_int<ChannelType> &rhs) {
            lhs /= rhs;
            return lhs;
        }

        color_grayscale_int<ChannelType>& operator++()
        {
            // actual increment takes place here
            ++this->value;
            return *this;
        }

        color_grayscale_int<ChannelType> operator++(int)
        {
            color_grayscale_int<ChannelType> tmp(*this); // copy
            operator++(); // pre-increment
            return tmp;   // return old value
        }
    };

    template<typename ChannelType> inline const color_grayscale_int<ChannelType> color_grayscale_int<ChannelType>::default_value = color_grayscale_int<ChannelType>(
            0);
    template<typename ChannelType> inline const color_grayscale_int<ChannelType> color_grayscale_int<ChannelType>::first_value = color_grayscale_int<ChannelType>(
            std::numeric_limits<ChannelType>::lowest());
    template<typename ChannelType> inline const color_grayscale_int<ChannelType> color_grayscale_int<ChannelType>::last_value = color_grayscale_int<ChannelType>(
            std::numeric_limits<ChannelType>::max());

    namespace colors {
        using grayscale8u = color_grayscale_int<uchar>;
        using grayscale16u = color_grayscale_int<ushort>;
        using grayscale8s = color_grayscale_int<char>;
        using grayscale16s = color_grayscale_int<short>;
        using grayscale32s = color_grayscale_int<int>;
        using mask = color_grayscale_int<uchar>;
        using labels16u = color_grayscale_int<ushort>;
        using labels32s = color_grayscale_int<int>;
        using labels = color_grayscale_int<int>;
    }
}

namespace std {
    template<typename ChannelType>
    struct hash<coixx::color_grayscale_int<ChannelType>> {
        size_t operator()(const coixx::color_grayscale_int<ChannelType> &x) const {
            return hash<typename coixx::color_grayscale_int<ChannelType>::raw_type>()(x);
        }
    };
}
