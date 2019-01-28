//
// Created by rgerst on 28.01.19.
//

#pragma once


#include <opencv2/opencv.hpp>

namespace cv {
    /**
     * Represents the relative coordinates of a rect inside another rect
     */
    class margin {

    public:

        /**
        * Creates this margin from the provided cv::Rect inside the rect defined by by the containing rect
        * @param t_rect
        * @param t_containing_rect
        */
        explicit margin(const cv::Rect &t_rect, const cv::Rect &t_containing_rect);

        /**
         * Creates this margin from the provided cv::Rect inside the rect defined by t_size (with x = 0 and y = 0)
         * @param t_rect
         * @param t_size
         */
        explicit margin(const cv::Rect &t_rect, const cv::Size &t_size);

        explicit margin(int t_left, int t_top, int t_right, int t_bottom);

        explicit margin(int t_all);

        margin();

        int get_left() const;

        int get_top() const;

        int get_right() const;

        int get_bottom() const;

        bool is_positive() const;

        bool is_negative() const;

        /**
         * Makes all values in the margin negative
         * @return
         */
        margin negate() const;

        /**
         * Converts the margin into an OpenCV rect
         * @param t_size
         * @return
         */
        cv::Rect to_rect(const cv::Rect &t_containing_rect) const;

        /**
         * Converts the margin into an OpenCV rect
         * @param t_size
         * @return
         */
        cv::Rect to_rect(const cv::Size &t_size) const;

    private:

        int m_left;
        int m_top;
        int m_right;
        int m_bottom;


    };
}

