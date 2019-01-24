//
// Created by rgerst on 25.07.18.
//


#pragma once

#include <misaxx/core/utils/type_traits.h>
#include <misaxx/imaging/coixx/image.h>

namespace coixx::converters {

    /**
     * Reinterprets the bytes of a color as another color.
     * Works in both directions (up-scaling and down-scaling), although it is required the the larger type must be dividable by
     * the smaller type.
     * To find the target size of the image, use reinterpret_converter::target_size
     * To convert with semantic behavior, use coixx::converters::semantic_convert.
     * To convert the values as-is without semantic behavior, use coixx::converters::hard_converter
     *
     * @tparam Csrc
     * @tparam Cdst
     */
    template<class Csrc, class Cdst> struct reinterpret_converter {

        static constexpr bool types_are_reinterpretable() {

            constexpr int i = sizeof(Csrc);
            constexpr int j = sizeof(Cdst);

            if constexpr (i <= j) {
                return j % i == 0;
            }
            else {
                return i % j == 0;
            }
        }

        static_assert(types_are_reinterpretable(), "Unable to reinterpret types safely: Sizes must be dividable!" );

        /**
         * Returns how many items are required as input
         * @return
         */
        static constexpr int get_input_factor() {
            constexpr int s = sizeof(Cdst) / sizeof(Csrc);
            if constexpr (s == 0) {
                return 1;
            }
            else {
                return s;
            }
        }

        /**
         * Returns how many items are required as output
         * @return
         */
        static constexpr int get_output_factor() {
            constexpr int s = sizeof(Csrc) / sizeof(Cdst);
            if constexpr (s == 0) {
                return 1;
            }
            else {
                return s;
            }
        }

        using input_color_type = std::array<Csrc, get_input_factor()>;
        using output_color_type = std::array<Cdst, get_output_factor()>;

        /**
         * Calculates the expected target size of the image if reinterpretation is applied.
         * @param t_input_size
         * @return
         */
        static cv::Size target_size(const cv::Size &t_input_size) {
            double factor = sizeof(Csrc) * 1.0 / sizeof(Cdst);
            return cv::Size(static_cast<int>(t_input_size.width * factor), static_cast<int>(t_input_size.height * factor));
        }

        /**
         * Converts one color into another color
         * @param t_color
         * @return
         */
        static std::array<Cdst, get_output_factor()> color(const input_color_type &t_color) {
            std::array<Cdst, get_output_factor()> output;
            auto *ptr = reinterpret_cast<typename output_color_type ::const_pointer >(t_color.data());
            *output.data() = *ptr;
            return output;
        }

        /**
         * Converts between two images
         * @param t_src
         * @param t_dst
         */
        static void image(const image<Csrc> &t_src, image<Cdst> &t_dst) {
            if(target_size(t_src.get_size()) != t_dst.get_size()) {
                throw std::runtime_error("Target size does not match!");
            }
            t_src.get_mat().convertTo(t_dst.get_mat(), t_dst.get_open_cv_type(), 1);
        }
    };

    /**
     * Applies reinterpret conversion of an image using a matching hard_converter.
     * This overload will convert to a copy. If conversion should be done in-place, use
     * hard_converter<Csrc, Cdst>::image() instead.
     *
     * See coixx::converters::reinterpret_converter class for more information.
     *
     * @tparam Csrc
     * @tparam Cdst
     * @param t_img
     * @return
     */
    template<class ImageDst, class Csrc, class Cdst = typename ImageDst::color_type> image<Cdst> reinterpret_convert(const image<Csrc> &t_img) {
        image<Cdst> target(reinterpret_converter<Csrc, Cdst>::target_size(t_img.get_size()));
        reinterpret_converter<Csrc, Cdst>::image(t_img, target);
        return target;
    }

    /**
    * Applies hard conversion of a color using a matching hard_converter.
    * @tparam Csrc
    * @tparam Cdst
    * @param t_color
    * @return
    */
    template<class Cdst, class Csrc> typename reinterpret_converter<Csrc, Cdst>::output_color_type reinterpret_convert(const typename reinterpret_converter<Csrc, Cdst>::input_color_type &t_color) {
        return reinterpret_converter<Csrc, Cdst>::color(t_color);
    }
}