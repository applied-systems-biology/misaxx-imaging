//
// Created by rgerst on 25.01.19.
//

#pragma once

namespace cv::toolbox {

    extern void binarize(cv::BMat &img, uchar threshold, uchar signal_value = 255, bool invert = false);

    extern void binarize(images::grayscale32f &img, float threshold, float signal_value = 1, bool invert = false);

    extern cv::BMat to_mask(const cv::BMat &img);

}



