//
// Created by rgerst on 29.01.19.
//


#pragma once

#include <misaxx/imaging/utils/cv2/BMat.h>

/**
 * More readable type definitions for static BMat
 */
namespace cv::images {
    using generic = Mat;
    using buffered = BMat;
    using grayscale8u = BMat1b;
    using grayscale16u = BMat1w;
    using grayscale16s = BMat1s;
    using grayscale32s = BMat1i;
    using grayscale32f = BMat1f;
    using grayscale64f = BMat1d;
    using mask = grayscale8u;
    using labels = grayscale32s;
    using labels_32s = grayscale32s;
    using labels_16u = grayscale16u;
}