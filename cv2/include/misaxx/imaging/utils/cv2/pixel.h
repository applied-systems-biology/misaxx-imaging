//
// Created by rgerst on 28.01.19.
//

#pragma once

#include <opencv2/core/types.hpp>

namespace cv {
    template<typename T> struct pixel {
        T value;
        cv::Point location;
    };
}




