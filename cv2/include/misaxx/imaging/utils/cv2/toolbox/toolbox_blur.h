//
// Created by rgerst on 28.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/static_types.h>

namespace cv::toolbox::blur {

    extern void median(images::grayscale &img, int ksize);

    extern void gauss(images::grayscale &img, double sigmax, double sigmay);

    extern void gauss(images::grayscale &img, double sigmaxy);
}


