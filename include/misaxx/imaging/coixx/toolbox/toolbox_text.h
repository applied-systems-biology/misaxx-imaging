//
// Created by rgerst on 13.07.18.
//


#pragma once

#include <opencv2/opencv.hpp>
#include <misaxx/imaging/coixx/toolbox/toolbox.h>

namespace coixx::toolbox::text {

    enum class font : int {
        hershey = cv::FONT_HERSHEY_PLAIN,
        hershey_simplex = cv::FONT_HERSHEY_SIMPLEX,
        hershey_duplex = cv::FONT_HERSHEY_DUPLEX,
        hershey_triplex = cv::FONT_HERSHEY_TRIPLEX,
        hershey_complex = cv::FONT_HERSHEY_COMPLEX,
        hershey_complex_small = cv::FONT_HERSHEY_COMPLEX_SMALL,
        hershey_script_simplex = cv::FONT_HERSHEY_SCRIPT_SIMPLEX,
        hershey_script_complex = cv::FONT_HERSHEY_SCRIPT_COMPLEX
    };

    enum class text_centering {
        none,
        vertical,
        horizontal,
        vertical_and_horizontal
    };

    /**
     * Object that holds most information about how the drawn text looks like
     */
    struct typeface {
        font text_font = font::hershey;
        double font_scale = 1;
        int line_thickness = 1;

        explicit typeface(font t_font = font::hershey, double t_font_scale = 1, int t_line_thickness = 1) :
                text_font(t_font), font_scale(t_font_scale), line_thickness(t_line_thickness) {

        }

        int get_opencv_font() const {
            return static_cast<int>(text_font);
        }

        /**
         * Measures the size of the text that would be created by this typeface
         * @param t_text
         * @return
         */
        cv::Size get_text_size(const std::string &t_text) const{
            return cv::getTextSize(t_text,get_opencv_font(), font_scale, line_thickness, nullptr);
        }
    };

    /**
     * Draws text at specific location
     * @tparam C
     * @param t_text
     * @param t_typeface
     * @param t_location
     * @param t_color
     * @return
     */
    template<class C> auto draw_text(const std::string &t_text, const typeface &t_typeface, const cv::Point &t_location, const C&t_color) {
        return [&](auto &t_img) {
            static_assert(traits::is_compatible<C>(t_img), "Text and image color must match!");
            cv::putText(t_img.get_mat(),
                        t_text,
                        t_location,
                        t_typeface.get_opencv_font(),
                        t_typeface.font_scale,
                        t_color.as_scalar(),
                        t_typeface.line_thickness);
        };
    }

    /**
     * Draws text, so it is centered around the input location.
     * @tparam C
     * @param t_text
     * @param t_typeface
     * @param t_location
     * @param t_color
     * @param t_centering
     * @return
     */
    template<class C> auto draw_text_centered(const std::string &t_text, const typeface &t_typeface, const cv::Point &t_location, const C&t_color, text_centering t_centering = text_centering::vertical_and_horizontal) {

        return [&t_text, &t_typeface, &t_location, &t_color, t_centering](auto &t_img) {

            if(t_centering == text_centering::none) {
                t_img << draw_text(t_text, t_typeface, t_location, t_color);
                return;
            }

            // This requires measurement!
            const auto text_size = t_typeface.get_text_size(t_text);

            cv::Point new_point(t_location);
            if(t_centering == text_centering::horizontal || t_centering == text_centering ::vertical_and_horizontal) {
                new_point.x -= text_size.width / 2;
            }
            if(t_centering == text_centering::vertical || t_centering == text_centering ::vertical_and_horizontal) {
                new_point.y -= text_size.height / 2;
            }

            t_img << draw_text(t_text, t_typeface, new_point, t_color);
        };
    }

}
