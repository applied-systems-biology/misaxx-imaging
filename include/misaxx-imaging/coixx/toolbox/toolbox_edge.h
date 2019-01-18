//
// Created by rgerst on 25.06.18.
//


#pragma once

#include <misaxx-imaging/coixx/toolbox/toolbox.h>

namespace coixx::toolbox::edge {
    /**
     * Applies a Laplacian filter to the image
     * @param t_sigma_x
     * @param t_sigma_y
     * @return
     */
    inline auto laplacian() {
        return [](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using channel_type = typename image_t::color_type::channel_type;
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");

            if constexpr (std::is_same<channel_type , int>::value) {

                for(int y = 0; y < t_img.get_image().rows; ++y) {

                    const auto * row_src_last = t_img.row_ptr(y - 1);
                    const auto * row_src = t_img.row_ptr(y);
                    const auto * row_src_next = t_img.row_ptr(y + 1);
                    auto * row_dst = t_img.get_image_buffer().row_ptr(y);

                    for(int x = 0; x < t_img.get_image().cols; ++x) {

                        const auto c = row_src[x];
                        const auto n = (y >= 1) ? row_src_last[x] : c;
                        const auto s = (y <= t_img.get_image().rows - 2) ? row_src_next[x] : c;
                        const auto e = (x <= t_img.get_image().rows - 2) ? row_src[x + 1] : c;
                        const auto w = (x >= 1) ? row_src[x - 1] : c;

                        // Calculate like this to prevent overflows
                        row_dst[x] = c - n + c - s + c - e + c - w;
                    }
                }

                t_img.apply_buffer();
            }
            else {
                cv::Laplacian(t_img.get_image(), t_img.get_image_buffer().get_image(), image_t::opencv_type);
                t_img.apply_buffer();
            }
        };
    }

    /**
     * Applies canny edge detector to image. Only grayscale8u images are supported.
     * @param t_threshold_low
     * @param t_threshold_high
     * @param t_aperture_size
     * @param t_l2_gradient
     * @return
     */
    inline auto canny(double t_threshold_low, double t_threshold_high, int t_aperture_size = 3, bool t_l2_gradient = false) {
        return [=](auto &t_img) {
            static_assert(traits::is_compatible<images::grayscale8u>(t_img), "Only 8 bit grayscale images are supported!");
            cv::Canny(t_img.get_image(), t_img.get_image_buffer().get_image(), t_threshold_low, t_threshold_high, t_aperture_size, t_l2_gradient);
            t_img.apply_buffer();
        };
    }

    /**
     * Applies Sobel filter to image
     * @param t_dx
     * @param t_dy
     * @return
     */
    inline auto sobel(int t_dx, int t_dy) {
        return [=](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(traits::is_floating_grayscale_image(t_img), "Must be a float or double image!");
            cv::Sobel(t_img.get_image(), t_img.get_image_buffer().get_image(), t_img.get_open_cv_type(), t_dx, t_dy);
            t_img.apply_buffer();
        };
    }

    /**
    * Applies a Sobel filter to the image
    * @return
    */
    inline auto sobel_x(int t_dx = 1) {
        return edge::sobel(t_dx, 0);
    }

    /**
    * Applies a Sobel filter to the image
    * @return
    */
    inline auto sobel_y(int t_dy = 1) {
        return edge::sobel(0, t_dy);
    }

    /**
     * Calculates the Sobel gradient G = sqrt(Gx^2 + Gy^2) where Gx and Gy are
     * the sobel filter responses in x and y direction.
     * @return
     */
    inline auto sobel_gradient() {
        return [](auto &t_img) {

            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using raw_type = typename image_t::raw_color_type;

            t_img << sobel_x();
            const images::raw img_gx = t_img.get_image().clone(); // Copy Gx from image
            t_img.apply_buffer(); // Swap back to the original image
            t_img << sobel_y();
            t_img.apply_buffer(); // Swap back to the original image. Gy is now in buffer
            const images::raw &img_gy = t_img.get_image_buffer().get_image();

            for(int y = 0; y < t_img.get_image().rows; ++y) {

                const auto * row_gx = img_gx.ptr<raw_type>(y);
                const auto * row_gy = img_gy.ptr<raw_type>(y);
                float * row = t_img.get_image().template ptr<raw_type>(y);

                for(int x = 0; x < t_img.get_image().cols; ++x) {
                    row[x] = sqrtf(powf(row_gx[x], 2) + powf(row_gy[x], 2));
                }
            }
        };
    }
}
