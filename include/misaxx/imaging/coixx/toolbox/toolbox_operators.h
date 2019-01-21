//
// Created by rgerst on 22.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/toolbox/toolbox.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_traits.h>

namespace coixx::toolbox::operators {

    /**
     * Adds the values of the other image to the target
     * @return
     */
    template<class Image2> inline auto add(const Image2 &t_other) {
        return [&t_other](auto &t_img) {
            static_assert(traits::is_same<Image2>(t_img), "Images must have same type!");
            t_img.get_image() += t_other.get_image();
        };
    }

    /**
     * Subtract the values of the other image from the target
     * @return
     */
    template<class Image2> inline auto subtract(const Image2 &t_other) {
        return [&t_other](auto &t_img) {
            static_assert(traits::is_same<Image2>(t_img), "Images must have same type!");
            t_img.get_image() -= t_other.get_image();
        };
    }

    /**
     * Multiplies the other image values with the target
     * @return
     */
    template<class Image2> inline auto multiply(const Image2 &t_other) {
        return [&t_other](auto &t_img) {
            static_assert(traits::is_same<Image2>(t_img), "Images must have same type!");
            t_img.get_image() *= t_other.get_image();
        };
    }

    /**
     * Divides the target by the other image values
     * @return
     */
    template<class Image2> inline auto divide(const Image2 &t_other) {
        return [&t_other](auto &t_img) {
            static_assert(traits::is_same<Image2>(t_img), "Images must have same type!");
            t_img.get_image() /= t_other.get_image();
        };
    }

}
