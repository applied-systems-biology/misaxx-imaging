//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/images/G_xU_BMat.h>
#include <misaxx/imaging/utils/cv2/SMat.h>

namespace cv {
    class G_16U_BMat : public SMat<ushort, CV_16UC(1), G_16U_BMat, G_xU_BMat> {
        using SMat<ushort, CV_16UC(1), G_16U_BMat, G_xU_BMat>::SMat;
    };
}




