//
// Created by rgerst on 25.07.18.
//


#pragma once

#include <misaxx/core/utils/type_traits.h>
#include <misaxx/imaging/coixx/image.h>

namespace coixx::converters {

    /**
     * Semantic conversion that produces a color in Cdst that is equivalent to the color in Csrc.
     * For example if colors::mask(255) is converted to colors::grayscale16u, the new color has a value of 65535, which is also white in
     * the target color space.
     * To convert without this semantic behavior, use coixx::converters::hard_converter
     *
     * This implementation applies to grayscale (arithmetric) images only.
     * For other color spaces, template specialization is required.
     *
     * @tparam Csrc
     * @tparam Cdst
     */
    template<class Csrc, class Cdst> struct semantic_converter {

        static_assert(std::is_arithmetic<typename Csrc::raw_type>::value && std::is_arithmetic<typename Cdst::raw_type>::value, "semantic_converter does not support this converters.");

        /**
         * Converts one color into another color
         * @param t_color
         * @return
         */
        static Cdst color(const Csrc &t_color) {
            if constexpr (!std::is_same<Csrc, Cdst>::value) {
                double scale_factor = (t_color - Csrc::first_value) * 1.0 / (Csrc::last_value - Csrc::first_value);
                double value = scale_factor * Cdst::last_value;
                return Cdst(cv::saturate_cast<typename Cdst::raw_type>(value));
            }
            else {
                return t_color;
            }
        }

        /**
         * Converts between two images
         * @param t_src
         * @param t_dst
         */
        static void image(const image<Csrc> &t_src, image<Cdst> &t_dst) {
            if constexpr (!std::is_same<Csrc, Cdst>::value) {
                double scale_factor = (Cdst::last_value - Cdst::first_value) * 1.0 / (Csrc::last_value - Csrc::first_value);
                t_src.get_mat().convertTo(t_dst.get_mat(), t_dst.get_open_cv_type(), scale_factor);
            }
            else {
                t_dst.get_mat() = t_src.get_mat().clone();
            }
        }
    };

    /**
     * Semantic conversion to bgr8u image
     * @tparam Csrc
     */
    template<class Csrc> struct semantic_converter<Csrc, colors::bgr8u > {


        /**
         * Converts between two images
         * @param t_src
         * @param t_dst
         */
        static void image(const image<Csrc> &t_src, images::bgr8u &t_dst) {
            if constexpr (!std::is_same<Csrc, colors::bgr8u>::value) {
                static_assert(std::is_same<Csrc, colors::bgr8u >::value ||
                              std::is_same<Csrc, colors::grayscale8u >::value ||
                              std::is_same<Csrc, colors::grayscale16u >::value ||
                              std::is_same<Csrc, colors::grayscale_float >::value,
                              "Only grayscale8u, grayscale16u or grayscale_float images can be converted!");

                if constexpr (std::is_same<Csrc, colors::grayscale8u>::value) {
                    cv::cvtColor(t_src.get_mat(), t_dst.get_mat(), cv::COLOR_GRAY2BGR);
                }
                else {
                    images::grayscale8u tmp(t_src.get_size());
                    semantic_converter<Csrc, colors::grayscale8u >::image(t_src, tmp);
                    cv::cvtColor(tmp.get_mat(), t_dst.get_mat(), cv::COLOR_GRAY2BGR);
                }

                assert(t_dst.get_mat().type() == colors::bgr8u::opencv_type);
            }
            else {
                t_dst.get_mat() = t_src.get_mat().clone();
            }
        }

        /**
         * Converts one color into another color
         * @param t_color
         * @return
         */
        static colors::bgr8u color(const Csrc &t_color) {
            if constexpr (!std::is_same<Csrc, colors::bgr8u >::value) {
                double scale_factor = (t_color.as_vec() - Csrc::first_value.as_vec()) * 1.0 / (Csrc::last_value.as_vec() - Csrc::first_value.as_vec());
                double value = scale_factor * 255;
                uchar value_conv = cv::saturate_cast<uchar>(value);
                return colors::bgr8u(value_conv, value_conv, value_conv);
            }
            else {
                return t_color;
            }
        }
    };

    /**
     * Specific semantic conversion between bgr8u and hsv8u
     */
    template<> struct semantic_converter<colors::bgr8u, colors::hsv8u > {

        /**
         * Converts one color into another color
         * @param t_color
         * @return
         */
        static colors::hsv8u color(const colors::bgr8u &t_color) {
            cv::Mat input(1, 1, CV_8UC3, t_color.as_scalar());
            cv::Mat output(1, 1, CV_8UC3);

            cv::cvtColor(input, output, cv::COLOR_BGR2HSV);

            return colors::hsv8u(output.at<cv::Vec3b>(0));
        }

        /**
        * Converts between two images
        * @param t_src
        * @param t_dst
        */
        static void image(const images::bgr8u &t_src, images::hsv8u &t_dst) {
            cv::cvtColor(t_src.get_mat(), t_dst.get_mat(), cv::COLOR_BGR2HSV);
        }
    };

    /**
     * Specific semantic conversion between bgr8u and hsv8u
     */
    template<> struct semantic_converter<colors::hsv8u , colors::bgr8u > {

        /**
         * Converts one color into another color
         * @param t_color
         * @return
         */
        static colors::bgr8u color(const colors::hsv8u &t_color) {
            cv::Mat input(1, 1, CV_8UC3, t_color.as_scalar());
            cv::Mat output(1, 1, CV_8UC3);

            cv::cvtColor(input, output, cv::COLOR_HSV2BGR);

            return colors::bgr8u(output.at<cv::Vec3b>(0));
        }

        /**
        * Converts between two images
        * @param t_src
        * @param t_dst
        */
        static void image(const images::hsv8u &t_src, images::bgr8u &t_dst) {
            cv::cvtColor(t_src.get_mat(), t_dst.get_mat(), cv::COLOR_HSV2BGR);
        }
    };

    /**
     * Applies semantic conversion of an image using a matching semantic_converter.
     * This overload will convert to a copy. If conversion should be done in-place, use
     * semantic_converter<Csrc, Cdst>::image() instead.
     * @tparam Csrc
     * @tparam Cdst
     * @param t_img
     * @return
     */
    template<class ImageDst, class Csrc, class Cdst = typename ImageDst::color_type> image<Cdst> semantic_convert(const image<Csrc> &t_img) {
        image<Cdst> target = image<Cdst>::allocate(t_img.get_size());
        semantic_converter<Csrc, Cdst>::image(t_img, target);
        return target;
    }

    /**
     * Applies semantic conversion of a color using a matching semantic_converter.
     * @tparam Csrc
     * @tparam Cdst
     * @param t_color
     * @return
     */
    template<class Cdst, class Csrc> Cdst semantic_convert(const Csrc &t_color) {
        return semantic_converter<Csrc, Cdst>::color(t_color);
    }
}