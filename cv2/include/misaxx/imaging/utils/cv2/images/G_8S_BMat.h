//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/SMat.h>

namespace cv {
    struct G_8S_BMat : public SMat<char, CV_8SC(1), G_8S_BMat, BMat> {
        using SMat<char, CV_8SC(1), G_8S_BMat, BMat>::SMat;
    };
}




