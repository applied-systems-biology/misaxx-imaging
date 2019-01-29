//
// Created by rgerst on 28.01.19.
//

#pragma once


#include <misaxx/imaging/utils/cv2/ReadableBMatTypes.h>

namespace cv::toolbox::normalize {
    extern void by_max(images::generic &img);
    extern void by_min_max(images::generic &img);
}



