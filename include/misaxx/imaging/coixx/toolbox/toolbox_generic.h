//
// Created by rgerst on 28.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/toolbox/toolbox.h>

namespace coixx::toolbox::generic {

    /**
     * Runs over the image and allows read access to the center value & the 4 adjacent values (cross pattern).
     * The cross pattern can extend outside of the image.
     * The center value has write access.
     * @tparam Function
     * @param t_function Function that takes values (c, n, s, e, w) and returns the destination color of the current pixel
     * @return
     */
    template<class Function, class C> inline auto grayscale_cross_inclusive(const Function &t_function, const C &t_outside_color) {
        return [=](auto &t_img) {

            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_type = typename image_t::color_type;

            static_assert(traits::is_grayscale(t_img), "Only grayscale images are supported");
            static_assert(traits::is_same<image<C>>(t_img), "Image type and color type do not match!");

            for (int y = 0; y < t_img.get_height(); ++y) {

                const color_type *row_src_last = y > 0 ? t_img.row_ptr(y - 1) : nullptr;
                const color_type *row_src = t_img.row_ptr(y);
                const color_type *row_src_next =  y - 1 < t_img.get_height() ? t_img.row_ptr(y + 1) : nullptr;
                color_type *row_dst = t_img.get_buffer_mat().template ptr<color_type>(y);

                for (int x = 0; x < t_img.get_width(); ++x) {

                    const color_type c = row_src[x];
                    const color_type n = (y >= 1) ? row_src_last[x] : c;
                    const color_type s = (y <= t_img.get_mat().rows - 2) ? row_src_next[x] : c;
                    const color_type e = (x <= t_img.get_mat().cols - 2) ? row_src[x + 1] : c;
                    const color_type w = (x >= 1) ? row_src[x - 1] : c;

                    // Calculate like this to prevent overflows
                    row_dst[x] = t_function(c, n, s, e, w);
                }
            }

            std::swap(t_img.get_mat(), t_img.get_buffer_mat());
        };
    }

}
