//
// Created by rgerst on 25.01.19.
//

#pragma once

#include <misaxx/imaging/utils/cv2/static_types.h>

namespace cv::toolbox {

    extern void binarize(images::grayscale8u &img, uchar threshold, uchar signal_value = 255, bool invert = false);

    extern void binarize(images::grayscale32f &img, float threshold, float signal_value = 1, bool invert = false);

}



