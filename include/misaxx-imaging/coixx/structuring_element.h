//
// Created by rgerst on 16.02.18.
//

#pragma once

#include <misaxx-imaging/coixx/image.h>

/**
 * Wrapper around cv::getStructuringElement
 * Use this to create structuring elements like circles or crosses for morphological operations
 * or other algorithms.
 */
namespace coixx::structuring_element {

    enum class type {
        rectangle = cv::MORPH_RECT,
        cross = cv::MORPH_CROSS,
        ellipse = cv::MORPH_ELLIPSE
    };

    extern images::mask get(type t_type, int t_width, int t_height);

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


