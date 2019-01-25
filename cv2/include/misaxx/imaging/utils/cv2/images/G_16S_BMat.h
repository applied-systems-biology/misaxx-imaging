//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/images/G_xS_BMat.h>
#include <misaxx/imaging/utils/cv2/SMat.h>

namespace cv {
    struct G_16S_BMat : public SMat<short, CV_16SC(1), G_xS_BMat> {
        using SMat<short, CV_16SC(1), G_xS_BMat>::SMat;
    };
}



