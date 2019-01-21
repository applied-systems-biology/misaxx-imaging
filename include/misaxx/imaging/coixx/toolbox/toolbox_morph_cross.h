//
// Created by rgerst on 28.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/toolbox/toolbox.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_generic.h>

namespace coixx::toolbox::morph {

    /**
     * Applies morphological dilation with a cross element.
     * This implementation supports integer images
     * @return
     */
    inline auto dilate_cross() {
        return [](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_type = typename image_t::color_type;
            t_img << generic::grayscale_cross_inclusive([](auto c, auto n, auto s, auto e, auto w) {
                return std::max({c, n, s, e, w});
            }, color_type::black());
        };
    }

    /**
     * Applies morphological erosion with a cross element.
     * This implementation supports integer images
     * @return
     */
    inline auto erode_cross() {
        return [](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_type = typename image_t::color_type;
            t_img << generic::grayscale_cross_inclusive([](auto c, auto n, auto s, auto e, auto w) {
                return std::min({c, n, s, e, w});
            }, color_type::black());
        };
    }

    /**
     * Applies morphological gradient with a cross element.
     * This implementation supports integer images
     * @return
     */
    inline auto gradient_cross() {
        return [](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_type = typename image_t::color_type;
            t_img << generic::grayscale_cross_inclusive([](auto c, auto n, auto s, auto e, auto w) {
                return std::max(0, std::max({c, n, s, e, w}) - std::min({c, n, s, e, w}));
            }, color_type::black());
        };
    }

    /**
     * For each pixel, check if the surrounding pixels have the same value.
     * If this is the case, set the pixel to 0, otherwise keep the value
     *
     * This method can be used to restrict label images to border-only
     * @return
     */
    inline auto sustaining_gradient_cross() {
        return [](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_type = typename image_t::color_type;
            t_img << generic::grayscale_cross_inclusive([](auto c, auto n, auto s, auto e, auto w) {
                return ((c == n) && (c == s) && (c == e) && (c == w)) ? 0 : c;
            }, color_type::black());
        };
    }

}
