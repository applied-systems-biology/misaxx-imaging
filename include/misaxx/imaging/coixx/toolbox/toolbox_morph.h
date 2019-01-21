//
// Created by rgerst on 22.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/toolbox/toolbox.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_values.h>
#include <stack>

namespace coixx::toolbox::morph {

    /**
    * Applies morphological dilation, which is equivalent to a maximum filter.
    * @tparam C
    * @tparam R
    * @param t_img
    * @param t_element
    * @param t_repeats
    */
    inline auto dilate( const images::mask &t_element, int t_repeats = 1) {
        return [&t_element, t_repeats](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(!traits::is_compatible<images::grayscale32s >(t_img), "Cannot be an integral grayscale image");

            cv::morphologyEx(t_img.get_image(),
                             t_img.get_image_buffer().get_image(),
                             cv::MORPH_DILATE,
                             t_element.get_image(),
                             cv::Point(-1,-1),
                             t_repeats,
                             cv::BORDER_CONSTANT, 0);

            t_img.apply_buffer();
        };
    }

    /**
    * Applies morphological erosion
    * @tparam C
    * @tparam R
    * @param t_img
    * @param t_element
    * @param t_repeats
    */
    inline auto erode( const images::mask &t_element, int t_repeats = 1) {
        return [&t_element, t_repeats](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(!traits::is_compatible<images::grayscale32s >(t_img), "Cannot be an integral grayscale image");

            cv::morphologyEx(t_img.get_image(),
                             t_img.get_image_buffer().get_image(),
                             cv::MORPH_ERODE,
                             t_element.get_image(),
                             cv::Point(-1,-1),
                             t_repeats,
                             cv::BORDER_CONSTANT, 0);

            t_img.apply_buffer();
        };
    }

    /**
    * Applies morphological opening, which is equivalent to dilate(erode(img))
    * @tparam C
    * @tparam R
    * @param t_img
    * @param t_element
    * @param t_repeats
    */
    inline auto open( const images::mask &t_element, int t_repeats = 1) {
        return [&t_element, t_repeats](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(!traits::is_compatible<images::grayscale32s >(t_img), "Cannot be an integral grayscale image");

            cv::morphologyEx(t_img.get_image(),
                             t_img.get_image_buffer().get_image(),
                             cv::MORPH_OPEN,
                             t_element.get_image(),
                             cv::Point(-1,-1),
                             t_repeats,
                             cv::BORDER_CONSTANT, 0);

            t_img.apply_buffer();
        };
    }

    /**
   * Applies morphological closing, which is equivalent to erode(dilate(img))
   * @tparam C
   * @tparam R
   * @param t_img
   * @param t_element
   * @param t_repeats
   */
    inline auto close( const images::mask &t_element, int t_repeats = 1) {
        return [&t_element, t_repeats](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(!traits::is_compatible<images::grayscale32s >(t_img), "Cannot be an integral grayscale image");

            cv::morphologyEx(t_img.get_image(),
                             t_img.get_image_buffer().get_image(),
                             cv::MORPH_CLOSE,
                             t_element.get_image(),
                             cv::Point(-1,-1),
                             t_repeats,
                             cv::BORDER_CONSTANT, 0);

            t_img.apply_buffer();
        };
    }

    /**
    * Applies morphological gradient, which is equivalent to morph_dilate(img) - morph_erode(img)
    * @tparam C
    * @tparam R
    * @param t_img
    * @param t_element
    * @param t_repeats
    */
    inline auto gradient( const images::mask &t_element, int t_repeats = 1) {
        return [&t_element, t_repeats](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(!traits::is_compatible<images::grayscale32s >(t_img), "Cannot be an integral grayscale image");

            cv::morphologyEx(t_img.get_image(),
                             t_img.get_image_buffer().get_image(),
                             cv::MORPH_GRADIENT,
                             t_element.get_image(),
                             cv::Point(-1,-1),
                             t_repeats,
                             cv::BORDER_CONSTANT, 0);

            t_img.apply_buffer();
        };
    }

    /**
   * Applies morphological tophat, which is equivalent to img - morph_open(img)
   * @tparam C
   * @tparam R
   * @param t_img
   * @param t_element
   * @param t_repeats
   */
    inline auto tophat( const images::mask &t_element, int t_repeats = 1) {
        return [&t_element, t_repeats](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(!traits::is_compatible<images::grayscale32s >(t_img), "Cannot be an integral grayscale image");

            cv::morphologyEx(t_img.get_image(),
                             t_img.get_image_buffer().get_image(),
                             cv::MORPH_TOPHAT,
                             t_element.get_image(),
                             cv::Point(-1,-1),
                             t_repeats,
                             cv::BORDER_CONSTANT, 0);

            t_img.apply_buffer();
        };
    }

    /**
   * Applies morphological blackhat, which is equivalent to morph_close(img) - img
   * @tparam C
   * @tparam R
   * @param t_img
   * @param t_element
   * @param t_repeats
   */
    inline auto blackhat( const images::mask &t_element, int t_repeats = 1) {
        return [&t_element, t_repeats](auto &t_img) {
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(!traits::is_compatible<images::grayscale32s >(t_img), "Cannot be an integral grayscale image");

            cv::morphologyEx(t_img.get_image(),
                             t_img.get_image_buffer().get_image(),
                             cv::MORPH_BLACKHAT,
                             t_element.get_image(),
                             cv::Point(-1,-1),
                             t_repeats,
                             cv::BORDER_CONSTANT, 0);

            t_img.apply_buffer();
        };
    }

    /**
   * Applies morphological hole closing
   * @tparam C
   * @tparam R
   * @param t_img
   * @param t_element
   * @param t_repeats
   */
    inline auto close_holes( const images::mask &t_element) {
        return [&t_element](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_t = typename image_t::color_type;
            using raw_type = typename image_t::color_type::raw_type;
            static_assert(traits::is_grayscale(t_img), "Must be a grayscale image");
            static_assert(!traits::is_compatible<images::grayscale32s >(t_img), "Cannot be an integral grayscale image");

            const raw_type value_1 = color_t::white();
            const raw_type value_0 = color_t::black();

            auto &img_buf = t_img.get_image_buffer().get_image();
            auto &img = t_img.get_image();

            img_buf = value_0; // Set to "0"

            std::vector<cv::Point> neighbors;
            std::stack<cv::Point> stack;

            t_element << values::get_if(std::back_inserter(neighbors), values::if_non_zero_pixel<colors::mask>());
            for(auto &neighbor : neighbors) {
                neighbor.x -= t_element.get_width() / 2;
                neighbor.y -= t_element.get_height() / 2;
            }

            // Find the points in x direction (1st dimension)
            cv::Point pos(0,0);

            int rows = img.rows;
            int cols = img.cols;

            for(int i = 0; i < rows; ++i) {
                pos.x = 0;

                if(img.template at<raw_type>(pos) == 0 && img_buf.template at<raw_type>(pos) == 0) {
                    img_buf.template at<raw_type>(pos) = value_1;
                    stack.push(pos);
                }

                pos.x = cols - 1;

                if(img.template at<raw_type>(pos) == 0 && img_buf.template at<raw_type>(pos) == 0) {
                    img_buf.template at<raw_type>(pos) = value_1;
                    stack.push(pos);
                }

                // Increase counter of y
                if(pos.y < rows) {
                    ++pos.y;
                }
                else {
                    pos.y = 0;
                }
            }

            pos = cv::Point(0,0);

            // Find the points in y direction (2nd dimension)

            for(int i = 0; i < cols; ++i) {
                pos.y = 0;

                if(img.template at<raw_type>(pos) == 0 && img_buf.template at<raw_type>(pos) == 0) {
                    img_buf.template at<raw_type>(pos) = value_1;
                    stack.push(pos);
                }

                pos.y = rows - 1;

                if(img.template at<raw_type>(pos) == 0 && img_buf.template at<raw_type>(pos) == 0) {
                    img_buf.template at<raw_type>(pos) = value_1;
                    stack.push(pos);
                }

                // Increase counter of y
                if(pos.x < cols) {
                    ++pos.x;
                }
                else {
                    pos.x = 0;
                }
            }

            // Apply
            while(!stack.empty()) {
                cv::Point pos = stack.top();
                stack.pop();

                for(const cv::Point & rel_neighbor : neighbors) {
                    cv::Point absolute = rel_neighbor + pos;

                    if(absolute.x >= 0 && absolute.y >= 0 && absolute.x < img.cols && absolute.y < img.rows) {
                        if(img.template at<raw_type>(absolute) == 0 && img_buf.template at<raw_type>(absolute) == 0) {
                            img_buf.template at<raw_type>(absolute) = value_1;
                            stack.push(absolute);
                        }
                    }
                }
            }

            t_img.apply_buffer();
            t_img << values::invert();
        };
    }

}
