//
// Created by rgerst on 19.07.18.
//


#pragma once

#include <unordered_map>
#include <misaxx/imaging/coixx/recoloring_map.h>
#include <misaxx/imaging/coixx/toolbox/toolbox.h>

namespace coixx::toolbox::recoloring {

    /**
     * Recolors between two images of different types.
     * @tparam Function Compatible function
     * @tparam ImageSrc
     * @tparam ImageDst
     * @param t_img_src
     * @param t_img_dst
     * @param t_function
     */
    template<class ImageSrc, class ImageDst, class Csrc = typename ImageSrc::color_type, class Cdst = typename ImageDst::color_type>
    inline void
    recolor_between(const ImageSrc &t_img_src, ImageDst &t_img_dst, const recoloring_map<Csrc, Cdst> &t_function) {

        assert_same_size(t_img_src, t_img_dst);

        for(int y = 0; y < t_img_src.get_height(); ++y) {
            const Csrc *row_src = t_img_src.row_ptr(y);
            Cdst *row_dst = t_img_dst.row_ptr(y);
            for(int x = 0; x < t_img_src.get_width(); ++x) {
                row_dst[x] = t_function.recolor(row_src[x]);
            }
        }
    }

    /**
     * Recolors the pixels within the image according to the recoloring function
     * @tparam Function
     * @param t_function
     * @param t_default_color
     * @return
     */
    template<class Csrc, class Cdst>
    inline auto recolor(const recoloring_map<Csrc, Cdst> &t_function) {
        return [&](auto &t_img) {
            for(int y = 0; y < t_img.get_height(); ++y) {
                Csrc *row = t_img.row_ptr(y);
                for(int x = 0; x < t_img.get_width(); ++x) {
                    row[x] = t_function.recolor(row[x]);
                }
            }
        };
    }

}
