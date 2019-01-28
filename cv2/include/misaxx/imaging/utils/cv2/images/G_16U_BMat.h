//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/SMat.h>

namespace cv {
    class G_16U_BMat : public SMat<ushort, CV_16UC(1), G_16U_BMat, BMat> {
        using SMat<ushort, CV_16UC(1), G_16U_BMat, BMat>::SMat;
    };
}




