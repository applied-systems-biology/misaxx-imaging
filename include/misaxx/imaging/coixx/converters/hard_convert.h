//
// Created by rgerst on 25.07.18.
//


#pragma once

#include <misaxx/core/utils/type_traits.h>
#include <misaxx/imaging/coixx/image.h>

namespace coixx::converters {

    /**
     * Hard conversion that produces a color in Cdst that may be not equivalent to the color in Csrc.
     * For example if colors::mask(255) is converted to colors::grayscale16u, the new color has a value of 255,
     * which changes the semantics.
     * To convert with semantic behavior, use coixx::converters::semantic_convert.
     * To reinterpret the bytes, use coixx::converters::reinterpret_convert
     *
     * This implementation does a saturate_cast without any scaling. If the type combination is not supported, template specialization
     * is required.
     *
     * @tparam Csrc
     * @tparam Cdst
     */
    template<class Csrc, class Cdst> struct hard_converter {

        /**
         * Converts one color into another color
         * @param t_color
         * @return
         */
        static Cdst color(const Csrc &t_color) {
            return Cdst(cv::saturate_cast<typename Cdst::raw_type>(t_color.as_vec()));
        }

        /**
         * Converts between two images
         * @param t_src
         * @param t_dst
         */
        static void image(const image<Csrc> &t_src, image<Cdst> &t_dst) {
            t_src.get_mat().convertTo(t_dst.get_mat(), t_dst.get_open_cv_type(), 1);
        }
    };

    /**
     * Applies hard conversion of an image using a matching hard_converter.
     * This overload will convert to a copy. If conversion should be done in-place, use
     * hard_converter<Csrc, Cdst>::image() instead.
     * @tparam Csrc
     * @tparam Cdst
     * @param t_img
     * @return
     */
    template<class ImageDst, class Csrc, class Cdst = typename ImageDst::color_type> image<Cdst> hard_convert(const image<Csrc> &t_img) {
        image<Cdst> target(t_img.get_size());
        hard_converter<Csrc, Cdst>::image(t_img, target);
        return target;
    }

    /**
    * Applies hard conversion of a color using a matching hard_converter.
    * @tparam Csrc
    * @tparam Cdst
    * @param t_color
    * @return
    */
    template<class Cdst, class Csrc> Cdst hard_convert(const Csrc &t_color) {
        return hard_converter<Csrc, Cdst>::color(t_color);
    }
}