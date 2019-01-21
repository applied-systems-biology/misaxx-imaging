//
// Created by rgerst on 04.05.18.
//


#pragma once

#include <opencv2/core/types.hpp>
#include <misaxx/imaging/coixx/image.h>

namespace coixx {

    /**
     * Wrapper around OpenCV contour
     */
    class contour {
    public:

        /**
         * Determines which contours are detected and how they relate to each other
         */
        enum class return_mode : int {
            external = cv::RETR_EXTERNAL,
            list = cv::RETR_LIST,
            hierarchy_2 = cv::RETR_CCOMP,
            tree = cv::RETR_TREE
        };

        enum class approximation : int {
            none = cv::CHAIN_APPROX_NONE,
            simple = cv::CHAIN_APPROX_SIMPLE,
            tc89_l1 = cv::CHAIN_APPROX_TC89_L1,
            tc89_kcos = cv::CHAIN_APPROX_TC89_KCOS
        };

        explicit contour(const images::mask &t_img, return_mode t_return_mode, approximation t_approx = approximation::simple);

        const std::vector<std::vector<cv::Point> > &get_contours() const;

        const std::vector<cv::Vec4i> &get_hierarchy() const;

    private:

        std::vector<std::vector<cv::Point> > m_contours;
        std::vector<cv::Vec4i> m_hierarchy;
    };
}