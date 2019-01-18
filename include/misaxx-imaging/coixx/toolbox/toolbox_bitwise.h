//
// Created by rgerst on 22.06.18.
//


#pragma once

#include <misaxx-imaging/coixx/image.h>
#include <misaxx-imaging/coixx/toolbox/toolbox.h>

namespace coixx::toolbox::bitwise {

    /**
     * Applies bitwise or operator between the input image and the other image.
     * @return
     */
    template<class C> inline auto OR(const image<C> &t_other ) {
        return [&t_other](image<C> &t_img) {
            static_assert(traits::is_integral_grayscale_image(t_img), "Must be an integral grayscale image");
            static_assert(traits::is_compatible<C>(t_img), "Images are incompatible to each other");

            cv::bitwise_or(t_img.get_image(), t_other.get_image(), t_img.get_image_buffer().get_image());
            t_img.apply_buffer();
        };
    }

    /**
     * Applies bitwise and operator between the input image and the other image.
     * @return
     */
    template<class C> inline auto AND(const image<C> &t_other ) {
        return [&t_other](image<C> &t_img) {
            static_assert(traits::is_integral_grayscale_image(t_img), "Must be an integral grayscale image");
            static_assert(traits::is_compatible<C>(t_img), "Images are incompatible to each other");

            cv::bitwise_and(t_img.get_image(), t_other.get_image(), t_img.get_image_buffer().get_image());
            t_img.apply_buffer();
        };
    }

    /**
     * Applies bitwise xor operator between the input image and the other image.
     * @return
     */
    template<class C> inline auto XOR(const image<C> &t_other ) {
        return [&t_other](image<C> &t_img) {
            static_assert(traits::is_integral_grayscale_image(t_img), "Must be an integral grayscale image");
            static_assert(traits::is_compatible<C>(t_img), "Images are incompatible to each other");

            cv::bitwise_xor(t_img.get_image(), t_other.get_image(), t_img.get_image_buffer().get_image());
            t_img.apply_buffer();
        };
    }

    /**
     * Applies bitwise xor operator between the input image and the other image.
     * @return
     */
    template<class C> inline auto NOT() {
        return [](image<C> &t_img) {
            static_assert(traits::is_integral_grayscale_image(t_img), "Must be an integral grayscale image");
            static_assert(traits::is_compatible<C>(t_img), "Images are incompatible to each other");

            cv::bitwise_not(t_img.get_image(), t_img.get_image_buffer().get_image());
            t_img.apply_buffer();
        };
    }

}
