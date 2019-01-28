//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/images/G_xU_xS_BMat.h>
#include <misaxx/imaging/utils/cv2/SMat.h>

namespace cv {
    struct G_32S_BMat : public SMat<int, CV_32SC(1), G_32S_BMat, G_xU_xS_BMat>{
        using SMat<int, CV_32SC(1), G_32S_BMat, G_xU_xS_BMat>::SMat;
    };
}


