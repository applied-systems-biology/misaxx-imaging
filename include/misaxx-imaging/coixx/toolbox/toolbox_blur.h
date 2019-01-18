//
// Created by rgerst on 21.06.18.
//


#pragma once

#include <misaxx-imaging/utils/percentiles.h>
#include <misaxx-imaging/coixx/image.h>
#include <misaxx-imaging/coixx/toolbox/toolbox.h>
#include <misaxx-imaging/coixx/toolbox/toolbox_utils.h>

namespace coixx::toolbox::blur {

    /**
     * Creates a Gaussian blur filter with specified x and y sigma
     * @param t_sigma_x
     * @param t_sigma_y
     * @return
     */
    inline auto gauss(double t_sigma_x, double t_sigma_y) {
        return [=](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");

            cv::GaussianBlur(t_img.get_image(), t_img.get_image_buffer().get_image(), cv::Size(0, 0), t_sigma_x, t_sigma_y);
            t_img.apply_buffer();
        };
    }

    /**
     * Creates a Gaussian blur filter with specified x and y sigma
     * @param t_sigma
     * @return
     */
    inline auto gauss(double t_sigma) {
        return toolbox::blur::gauss(t_sigma, t_sigma);
    }

    /**
     * Filters the image with a box filter
     * @param t_size_x
     * @param t_size_y
     * @return
     */
    inline auto mean(int t_size_x, int t_size_y) {
        return [=](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");

            cv::blur(t_img.get_image(), t_img.get_image_buffer().get_image(),cv::Size(t_size_x,  t_size_y));
            t_img.apply_buffer();
        };
    }

    /**
     * Filters the image with a box filter
     * @param t_size
     * @return
     */
    inline auto mean(int t_size) {
        return toolbox::blur::mean(t_size, t_size);
    }

    /**
     * Filters the image with a median filter
     * @param t_size Must be an odd size
     * @return
     */
    inline auto median(int t_size) {
        return [=](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(!traits::is_same<images::grayscale32s>(t_img), "Integer images are not supported!");
            if(t_size % 2 == 0) throw std::runtime_error("The size must be odd!");

            cv::medianBlur(t_img.get_image(), t_img.get_image_buffer().get_image(),t_size);
            t_img.apply_buffer();
        };
    }

//    /**
//     * Applies median filter with a cross pattern. Outside pixels are assumed to be black.
//     * Works with integer images.
//     * @return
//     */
//    inline auto median_cross() {
//        return [](auto &t_img) {
//            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
//
//            using image_t = typename std::remove_reference<decltype(t_img)>::type;
//            using raw_type = typename image_t::raw_color_type;
//
//            t_img.ensure_buffer_image();
//
//            std::vector<raw_type> buffer(5);
//
//            for(int y = 0; y < t_img.get_height(); ++y) {
//
//                const auto *row = t_img.row_ptr(y);
//                const auto *row_prev = y > 0 ? t_img.row_ptr(y - 1) : nullptr;
//                const auto *row_next = y + 1 < t_img.get_height() ? t_img.row_ptr(y + 1) : nullptr;
//                auto *row_target = t_img.get_image_buffer().get_image().template ptr<raw_type>(y);
//
//                for(int x = 0; x < t_img.get_width(); ++x) {
//
//                    buffer[0] = row[x];
//                    buffer[1] = row_prev != nullptr ? row_prev[x] : 0;
//                    buffer[2] = row_next != nullptr ? row_next[x] : 0;
//                    buffer[3] = x + 1 < t_img.get_width() ? row[x + 1] : 0;
//                    buffer[4] = x > 0 ? row[x - 1] : 0;
//
//                    row_target[x] = misaxx_imaging::utils::percentiles::find_percentile(buffer, 50);
//
//                }
//            }
//
//        };
//    }

}
