//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/images/G_xF_BMat.h>
#include <misaxx/imaging/utils/cv2/SMat.h>

namespace cv {
    /**
     * Buffered cv::Mat of CV_32FC1 (Greyscale)
     */
    struct G_32F_BMat : public SMat<float, CV_32FC(1), G_32F_BMat, G_xF_BMat> {
        using SMat<float, CV_32FC(1), G_32F_BMat, G_xF_BMat>::SMat;
    };
}




