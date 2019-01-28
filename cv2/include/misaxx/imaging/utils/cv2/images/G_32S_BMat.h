//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/SMat.h>

namespace cv {
    struct G_32S_BMat : public SMat<int, CV_32SC(1), G_32S_BMat, BMat>{
        using SMat<int, CV_32SC(1), G_32S_BMat, BMat>::SMat;
    };
}


