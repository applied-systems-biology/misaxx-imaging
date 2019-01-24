//
// Created by rgerst on 25.06.18.
//


#pragma once

#include <string>
#include <misaxx/imaging/coixx/toolbox/toolbox.h>
#include <opencv2/highgui.hpp>

namespace coixx::toolbox {

    /**
     * Clones the image
     * @tparam C
     * @param t_img
     * @return
     */
    template<class C> image<C> clone(const image<C> &t_img) {
        return t_img.clone();
    }

    /**
     * Shows the current image using OpenCV HighGUI
     * @param t_title
     * @return
     */
    inline auto show(const std::string &t_title) {
        return [&](auto &t_img) {
            cv::namedWindow(t_title, cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_EXPANDED);
            cv::imshow(t_title, t_img.get_mat());
        };
    }

    /**
     * Shows the current image using OpenCV HighGUI and waits until all windows are closed
     * @param t_title
     * @return
     */
    inline auto show_and_wait(const std::string &t_title) {
        return [&](auto &t_img) {
            cv::namedWindow(t_title, cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_EXPANDED);
            cv::imshow(t_title, t_img.get_mat());
            cv::waitKey(0);
        };
    }

    /**
     * Swaps the buffer and image data
     * @return
     */
    inline auto swap_buffer() {
        return [](auto &t_img) {
            std::swap(t_img.get_mat(), t_img.get_buffer_mat());
        };
    }

}
