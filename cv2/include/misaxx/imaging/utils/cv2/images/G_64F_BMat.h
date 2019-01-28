//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/SMat.h>

namespace cv {
    struct G_64F_BMat : public SMat<double, CV_64FC(1), G_64F_BMat, BMat> {
        using SMat<double, CV_64FC(1), G_64F_BMat, BMat>::SMat;
    };
}


