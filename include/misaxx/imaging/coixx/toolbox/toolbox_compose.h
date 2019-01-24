//
// Created by rgerst on 26.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/image.h>
#include <misaxx/imaging/coixx/toolbox/toolbox.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_mask.h>

namespace coixx::toolbox::compose {

    /**
     * Overlays the input image with the other image where the mask is white.
     * @tparam C
     * @param t_other
     */
    template<class C> inline auto overlay_with(const image<C> &t_other, const images::mask &t_mask) {
        return[&](image<C> &t_img) {
            assert_same_size(t_img, t_other);
            if constexpr (std::is_same<C, colors::grayscale32s>::value) {
                // OpenCV does not support int32 setting
                for(int y = 0; y < t_img.get_height(); ++y) {
                    auto *row = t_img.row_ptr(y);
                    const auto *row_other = t_other.row_ptr(y);
                    const auto *row_mask = t_mask.row_ptr(y);

                    for(int x = 0; x < t_img.get_width(); ++x) {
                        row[x] = row_mask[x].is_foreground() ? row_other[x] : row[x];
                    }
                }
            }
            else {
                images::raw &raw = t_img.get_mat();
                raw.setTo(t_other.get_mat(), t_mask.get_mat());
            }
        };
    }

    /**
     * Overlays the input image with the other image where the other image is not background.
     * The background are all pixels that are black.
     * @tparam C
     * @param t_other
     */
    template<class C> inline auto overlay_with(const image<C> &t_other) {
        return[&](image<C> &t_img) {
            assert_same_size(t_img, t_other);
            images::mask mask = mask::from(t_other);
            t_img << overlay_with(t_other, mask);
        };
    }

    /**
     * Merges the images together using alpha blending
     * @tparam C
     * @param t_other
     * @param t_alpha
     * @return
     */
    template<class C> inline auto blend_with(const image<C> &t_other, double t_alpha) {
        return [&t_other,t_alpha](image<C> &t_img) {
            assert_same_size(t_img, t_other);
            cv::addWeighted(t_img.get_mat(), t_alpha, t_other.get_mat(), 1.0 - t_alpha, 0.0, t_img.get_buffer_mat());
            std::swap(t_img.get_mat(), t_img.get_buffer_mat());
        };
    }

    /**
     * Generic implementation of pixel-wise operations
     * @tparam C
     * @tparam Function
     * @param t_other
     * @param t_operator
     * @return
     */
    template<class C, typename Function> inline auto pixel_wise(const image<C> &t_other, const Function &t_function) {
        return[&t_other, t_function](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Only grayscale images are allowed!");
            static_assert(traits::is_same<image<C>>(t_img), "Image types are different!");

            for (int y = 0; y < t_img.get_mat().rows; ++y) {
                const auto *row_other = t_other.row_ptr(y);
                auto *row = t_img.row_ptr(y);

                for (int x = 0; x < t_img.get_mat().cols; ++x) {
                    row[x] = t_function(row[x], row_other[x]);
                }
            }
        };
    }

    /**
     * Pixel-wise max operation
     * @tparam C
     * @param t_other
     * @return
     */
    template<class C> inline auto pixel_wise_max(const image<C> &t_other) {
        return pixel_wise(t_other, [](auto a, auto b){ return std::max(a, b); });
    }

}
