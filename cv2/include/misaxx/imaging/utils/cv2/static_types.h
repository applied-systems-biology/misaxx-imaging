//
// Created by rgerst on 25.01.19.
//


#pragma once

#include <misaxx/imaging/utils/cv2/images/G_8U_BMat.h>
#include <misaxx/imaging/utils/cv2/images/G_8S_BMat.h>
#include <misaxx/imaging/utils/cv2/images/G_16U_BMat.h>
#include <misaxx/imaging/utils/cv2/images/G_16S_BMat.h>
#include <misaxx/imaging/utils/cv2/images/G_32S_BMat.h>
#include <misaxx/imaging/utils/cv2/images/G_32F_BMat.h>
#include <misaxx/imaging/utils/cv2/images/G_64F_BMat.h>

/**
 * Contains convenient static
 */
namespace cv::images {
    using generic = Mat;
    using buffered = BMat;
    using grayscale = G_BMat;
    using grayscale_unsigned_integer = G_xU_BMat;
    using grayscale_signed_integer = G_xS_BMat;
    using grayscale_floating = G_xF_BMat;
    using grayscale_integer = G_xU_xS_BMat;
    using grayscale8u = G_8U_BMat;
    using grayscale8s = G_8S_BMat;
    using grayscale16u = G_16U_BMat;
    using grayscale16s = G_16S_BMat;
    using grayscale32s = G_32S_BMat;
    using grayscale32f = G_32F_BMat;
    using grayscale64f = G_64F_BMat;
    using mask = grayscale8u;
    using labels = grayscale32s;
    using labels_32s = grayscale32s;
    using labels_16u = grayscale16u;
}