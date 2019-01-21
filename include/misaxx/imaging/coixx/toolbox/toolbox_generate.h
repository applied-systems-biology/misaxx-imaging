//
// Created by rgerst on 26.03.18.
//


#pragma once

#include <misaxx/imaging/coixx/image.h>
#include <misaxx/imaging/coixx/image.h>
#include <misaxx/imaging/coixx/toolbox/toolbox.h>

namespace coixx::toolbox::generate {

    /**
     * Draws a grid onto the target
     * @tparam C
     * @param t_target
     * @param t_grid_size_x
     * @param t_grid_size_y
     * @param t_grid_offset_x
     * @param t_grid_offset_y
     */
    template<class C> inline void grid(image<C> &t_target, const C &t_color, const int t_grid_size_x, const int t_grid_size_y, const int t_grid_offset_x = 0, const int t_grid_offset_y = 0) {

        static_assert(traits::is_grayscale(t_target), "Only grayscale images are supported!");

        for(int y = 0; y < t_target.get_size().height; ++y) {
            auto *row = t_target.row_ptr(y);
            for(int x = 0; x < t_target.get_size().width; ++x) {
                const bool has_x = (x - t_grid_offset_x) % t_grid_size_x == 0;
                const bool has_y = (y - t_grid_offset_y) % t_grid_size_y == 0;
                if(has_x || has_y) {
                    row[x] = t_color;
                }
            }
        }
    }

    /**
     * Draws many circles with the same radius onto the target image
     * @tparam C
     * @param t_target
     * @param t_centers
     * @param t_radius
     */
    template<class C> inline void circles(image<C> &t_target, const std::vector<cv::Point> &t_centers, const double t_radius, const C& t_color) {
        const double r_sq = pow(t_radius, 2);

        static_assert(traits::is_grayscale(t_target), "Only grayscale images are supported!");
        for(int y = 0; y < t_target.get_image().rows; ++y) {

            auto *row = t_target.row_ptr(y);

            for(int x = 0; x < t_target.get_image().cols; ++x) {
                for(const auto &point : t_centers) {
                    const double l = pow(x - point.x, 2) + pow(y - point.y, 2);

                    if(l <= r_sq) {
                        row[x] = t_color;
                        break;
                    }
                }
            }
        }

    }

}
