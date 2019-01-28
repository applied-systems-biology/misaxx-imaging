//
// Created by rgerst on 25.01.19.
//

#pragma once

#include <misaxx/imaging/utils/cv2/images/G_xU_BMat.h>
#include <misaxx/imaging/utils/cv2/SMat.h>

namespace cv {
    /**
     * Buffered cv::Mat of CV_8UC1 (Greyscale)
     */
    struct G_8U_BMat : public SMat<uchar, CV_8UC(1), G_8U_BMat, G_xU_BMat> {
        using SMat<uchar, CV_8UC(1), G_8U_BMat, G_xU_BMat>::SMat;
    };

}




