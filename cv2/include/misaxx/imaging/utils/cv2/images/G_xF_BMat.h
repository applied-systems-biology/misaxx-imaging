//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/images/G_BMat.h>

namespace cv {
    /**
     * BMat that contains greyscale floating point pixels
     */
    struct G_xF_BMat : public G_BMat {
        using G_BMat::G_BMat;
    };
}



