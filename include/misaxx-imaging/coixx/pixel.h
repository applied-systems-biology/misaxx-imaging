//
// Created by rgerst on 06.03.18.
//


#pragma once

#include <opencv2/opencv.hpp>

/**
 * Stores a pixel of a given color.
 * Can be implicity converted into a cv::Point, a high-level color or the raw color value.
 * @tparam C
 */
template<class C> class pixel {

public:

    using raw_type = typename C::raw_type;

    pixel() = default;

    pixel(int t_x, int t_y, C t_value) : x(t_x), y(t_y), value(t_value) {

    }

    int x = 0;
    int y = 0;
    C value;

    /**
     * Converts the pixel to the high-level color
     * @return
     */
    operator C() const {
        return value;
    }

    /**
     * Converts the pixel to the point coordinates
     * @return
     */
    operator cv::Point() const {
        return cv::Point(x, y);
    }

    /**
     * Converts the pixel to the raw color value
     * @return
     */
    operator raw_type() const {
        return value.get_value();
    }

};