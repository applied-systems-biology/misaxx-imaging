//
// Created by rgerst on 29.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/ReadableBMatTypes.h>

namespace cv::toolbox {
    void clamp(cv::images::generic &img, double from, double to);

    void clamp_below(cv::images::generic &img, double from);

    void clamp_above(cv::images::generic &img, double to);
}



