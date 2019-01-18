//
// Created by rgerst on 22.06.18.
//


#pragma once

#include <misaxx/utils/ref.h>
#include <misaxx-imaging/coixx/toolbox/toolbox.h>
#include <misaxx-imaging/coixx/toolbox/toolbox_statistics.h>
#include <misaxx-imaging/coixx/thresholding.h>

namespace coixx::toolbox::binarize {

    /**
     * Sets all pixels with a value greater than the threshold to the target color.
     * The target color defaults to the maximum supported color of the color space.
     * @tparam Image
     * @param t_threshold
     * @return
     */
    template<class C> inline auto threshold(C t_threshold, C t_target = C::last_value) {
        return [t_threshold, t_target](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(traits::is_compatible<C>(t_img), "Image types do not match");

            cv::threshold(t_img.get_image(), t_img.get_image_buffer().get_image(), t_threshold, t_target, cv::THRESH_BINARY);
            t_img.apply_buffer();
        };
    }

    /**
     * Applies Otsu thresholding to the image. Only works on images::mask / images::grayscale8u
     * @param t_threshold
     * @return
     */
    inline auto otsu(const misaxx::utils::ref<uchar> &t_threshold = std::nullopt ) {
        return [&t_threshold](images::mask &t_img) {
            double t = cv::threshold(t_img.get_image(), t_img.get_image_buffer().get_image(), 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
            t_img.apply_buffer();
            misaxx::utils::try_assign_ref(t_threshold, static_cast<uchar>(t));
        };
    }

    /**
     * Applies Otsu thresholding to the image. Only works on images::mask / images::grayscale8u
     * @param t_threshold
     * @return
     */
    inline auto otsu_where(const images::mask &t_mask, const misaxx::utils::ref<uchar> &t_threshold = std::nullopt ) {
        return [&t_threshold, &t_mask](images::mask &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");

            const auto histogram = statistics::get_histogram_where(t_img, t_mask);

            uchar t = math::otsu<colors::mask>(histogram);
            t_img << threshold(colors::mask(t));

            misaxx::utils::try_assign_ref(t_threshold, t);
        };
    }
}
