//
// Created by rgerst on 22.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/toolbox/toolbox.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_operators.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_values.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_binarize.h>
#include <misaxx/imaging/coixx/converters/semantic_convert.h>

namespace coixx::toolbox::normalize {

    /**
     * Applies max normalization filter to the image.
    * Calculates for each pixel: I^(x,y) = (I(x,y) * HIGHEST_POSSIBLE_VALUE) / max{ I(i,j) }{i,j}
    * Will not do anything if the maximum is 0
     * @return
     */
    inline auto by_max() {
        return [](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_t = typename image_t::color_type;
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");

            const auto max_value = statistics::max(t_img);
            const auto max_possible_value = color_t::last_value;

            if (max_value == 0)
                return;

            for (int y = 0; y < t_img.get_image().rows; ++y) {
                auto *row = t_img.row_ptr(y);
                for (int x = 0; x < t_img.get_image().cols; ++x) {
                    row[x] = color_t((row[x] * max_possible_value) / max_value);
                }
            }
        };
    }

    /**
     * Normalizes the image, so the values between min and max stretch across the whole color range.
     * Calculates for each pixel: I^(x,y) = (I(x,y) - MIN_VALUE) / (MAX_VALUE - MIN_VALUE) * HIGHEST_POSSIBLE_VALUE
     * All values outside the color space are truncated to the respective minimum and maximum value.
     * @tparam Image
     * @param t_min
     * @param t_max
     * @return
     */
    template<class C> inline auto by_min_max(C t_min, C t_max) {
        return [=](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(traits::is_same<image<C>>(t_img), "Image type does not match color type!");
            using image_t = typename std::remove_reference<decltype(t_img)>::type;

            double dmin = t_min;
            double dmax = t_max;
            double max_supported = image_t::color_type::last_value;
            double min_supported = image_t::color_type::first_value;

            for(int y = 0; y < t_img.get_height(); ++y) {
                auto *row = t_img.row_ptr(y);
                for(int x = 0; x < t_img.get_width(); ++x) {
                    row[x] = static_cast<C>(std::clamp((row[x] - dmin) / (dmax - dmin) * max_supported, min_supported, max_supported));
                }
            }
        };
    }

    /**
     * Like by_min_max(t_min, t_max), but t_min and t_max are calculated from the actual minimum and maximum value of the image.
     *
     * @tparam Image
     * @param t_min
     * @param t_max
     * @return
     */
    inline auto by_min_max() {
        return [](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_type = typename image_t::color_type;
            color_type dmin;
            color_type dmax;
            statistics::min_max(t_img, dmin, dmax);

            t_img << by_min_max(dmin, dmax);
        };
    }

    /**
     * Normalizes the image by the min and max value of a region
     * Calculates for each pixel: I^(x,y) = (I(x,y) - MIN_VALUE) / (MAX_VALUE - MIN_VALUE) * HIGHEST_POSSIBLE_VALUE
     * @return
     */
    inline auto by_min_max_where(const images::mask &t_region) {
        return [&t_region](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");

            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using raw_type = typename image_t::raw_color_type;
            using color_type = typename image_t::color_type;

            color_type dmin;
            color_type dmax;
            statistics::min_max_where(t_img, dmin, dmax, t_region);

            t_img << normalize::by_min_max(dmin, dmax);
        };
    }

    /**
     * Normalizes the by min-maxing between the provided percentiles
     * @param t_lower_percentile
     * @param t_higher_percentile
     * @return
     */
    inline auto by_percentiles(double t_lower_percentile, double t_higher_percentile) {
        return [=](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");

            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_type = typename image_t::color_type;

            if(t_lower_percentile >= t_higher_percentile) {
                throw std::runtime_error("Lower percentile must be lower than the higher percentile!");
            }

            std::vector<color_type > percentiles;
            statistics::get_percentiles(t_img, { t_lower_percentile, t_higher_percentile }, percentiles);
            t_img << by_min_max(percentiles[0], percentiles[1]);
        };
    }

    /**
     * First normalizes the image by the lower percentile, making it the minimum intensity.
     * Then normalizes by the higher percentile afterwards, making it the maximum intensity.
     * This algorithm is different from by_percentile!
     * @param t_lower_percentile
     * @param t_higher_percentile
     * @return
     */
    inline auto by_percentiles_2(double t_lower_percentile, double t_higher_percentile) {
        return [=](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");

            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_type = typename image_t::color_type;

            if(t_lower_percentile >= t_higher_percentile) {
                throw std::runtime_error("Lower percentile must be lower than the higher percentile!");
            }

            color_type low_percentile = statistics::get_percentile(t_img, t_lower_percentile);
            t_img << values::clamp_below(color_type(low_percentile));
            t_img.get_image() -= low_percentile.as_vec();
            color_type high_percentile = statistics::get_percentile(t_img, t_higher_percentile);
            t_img << values::clamp_above(color_type(high_percentile));
            t_img << normalize::by_max();
        };
    }

    /**
     * Calculates t_percentile and (1 - t_percentile) percentiles and determines if the t_percentile's percentile is
     * larger than the minimum signal value. If this is the case, normalizes between the upper and lower percentile.
     * If t_percentile is 100, this the upper percentile is the maximum value, while the lower percentile is the minimum value.
     * This is equivalent to by_min_max
     * @param t_percentile
     * @param t_min_signal_value
     * @return
     */
    template<class C> inline auto by_percentile_and_min_signal(double t_percentile, C t_min_signal_value) {
        return [=](auto &t_img) {

            using image_t = typename std::remove_reference<decltype(t_img)>::type;

            auto &img_buf = t_img.get_image_buffer().get_image();
            auto &img = t_img.get_image();

            if(t_percentile < 100) {

                std::vector<C> percentiles;
                statistics::get_percentiles(t_img, { t_percentile, 100.0 - t_percentile }, percentiles);

                double upper_percentile = percentiles[0];
                double lower_percentile = percentiles[1];

                if(upper_percentile > t_min_signal_value) {
                    img = img - lower_percentile;
                    cv::threshold(img, img_buf, upper_percentile - lower_percentile, 0, cv::THRESH_TRUNC);
                    t_img.apply_buffer();

                    t_img << by_max();
                }
                else {
                    img = 0;
                }
            }
            else {

                if(statistics::max(t_img) < t_min_signal_value) {
                    img = 0;
                }
                else {
                    // Percentile converges to max(image) with increasing percentile
                    // Collapses into MINMAX normalization
                    t_img << normalize::by_min_max();
                }
            }
        };
    }

    /**
     * Finds the reference region by applying Otsu thresholding and determines an upper intensity as average of this region.
     * Values are cut off after this threshold. Then by_max normalization is applied.
     * @return
     */
    inline auto by_avg_otsu() {
        return [](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_type = typename image_t::color_type;

            auto mask = converters::semantic_convert<images::mask>(t_img) << binarize::otsu();
            auto threshold = statistics::get_mean_where(t_img, mask);
            t_img << values::clamp_above(color_type(threshold)) << by_max();
        };
    }

    /**
     * Subtracts the background from the image. The background is estimated with a blur function.
     * @tparam BlurFunction
     * @param t_blur_function
     * @return
     */
    template<class BlurFunction> inline auto background_subtraction(const BlurFunction &t_blur_function) {
        return [&t_blur_function](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");

            auto local_brightness = t_img.clone();
            local_brightness << t_blur_function;
            t_img -= local_brightness;
            t_img << normalize::by_max();

        };
    }

    /**
     * Divides the image by the background. The background is estimated with a blur function.
     * @tparam BlurFunction
     * @param t_blur_function
     * @return
     */
    template<class BlurFunction> inline auto background_division(const BlurFunction &t_blur_function) {
        return [&t_blur_function](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            t_img << operators::divide(t_img.clone() << t_blur_function) << values::clamp();
        };
    }

}
