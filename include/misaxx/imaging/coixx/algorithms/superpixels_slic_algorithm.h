//
// Created by ruman on 17.12.18.
//

#pragma once

#include <opencv2/ximgproc.hpp>

namespace coixx {

    /**
     * Available algorithms for SLIC superpixel method
     */
    enum class superpixels_slic_algorithm : int {
        /**
         * Optimizes to desired region size
         */
                SLIC = cv::ximgproc::SLIC,
        /**
         * Optimizes by adaptive compactness factor
         */
                SLICO = cv::ximgproc::SLICO,
        /**
         * Uses manifold method for more context-sensitiveness
         */
                MSLIC = cv::ximgproc::MSLIC
    };
}