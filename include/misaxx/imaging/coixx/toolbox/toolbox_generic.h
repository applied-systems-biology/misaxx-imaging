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

            static_assert(traits::is_grayscale(t_img), "Only grayscale images are supported");
            static_assert(traits::is_same<image<C>>(t_img), "Image type and color type do not match!");

            for (int y = 0; y < t_img.get_height(); ++y) {

                const auto *row_src_last = y > 0 ? t_img.row_ptr(y - 1) : nullptr;
                const auto *row_src = t_img.row_ptr(y);
                const auto *row_src_next =  y - 1 < t_img.get_height() ? t_img.row_ptr(y + 1) : nullptr;
                auto *row_dst = t_img.get_image_buffer().row_ptr(y);

                for (int x = 0; x < t_img.get_width(); ++x) {

                    const auto c = row_src[x];
                    const auto n = (y >= 1) ? row_src_last[x] : c;
                    const auto s = (y <= t_img.get_image().rows - 2) ? row_src_next[x] : c;
                    const auto e = (x <= t_img.get_image().cols - 2) ? row_src[x + 1] : c;
                    const auto w = (x >= 1) ? row_src[x - 1] : c;

                    // Calculate like this to prevent overflows
                    row_dst[x] = t_function(c, n, s, e, w);
                }
            }

            t_img.apply_buffer();
        };
    }

}
