//
// Created by rgerst on 28.01.19.
//

#pragma once

#include <opencv2/imgproc.hpp>
#include <misaxx/imaging/utils/cv2/ReadableBMatTypes.h>

namespace cv {
    enum class structuring_element_type {
        rectangle = cv::MORPH_RECT,
        cross = cv::MORPH_CROSS,
        ellipse = cv::MORPH_ELLIPSE
    };
}

namespace cv::structuring_element {

    extern images::mask get(structuring_element_type t_type, int t_width, int t_height);

    extern images::mask rectangle(int t_width, int t_height);

    extern images::mask rectangle(int t_size);

    extern images::mask square(int t_size);

    extern images::mask ellipse(int t_width, int t_height);

    extern images::mask ellipse(int t_size);

    extern images::mask cross(int t_width, int t_height);

    extern images::mask cross(int t_size = 3);

    extern images::mask circle(int t_size);

    /**
     * Structuring element that is a circle with a 1px hole in the center
     * @param t_size
     * @return
     */
    extern images::mask circle_with_hole(int t_size);

}



