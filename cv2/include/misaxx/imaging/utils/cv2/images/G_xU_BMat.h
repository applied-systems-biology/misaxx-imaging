//
// Created by rgerst on 25.01.19.
//

#pragma once

#include <misaxx/imaging/utils/cv2/images/G_xU_xS_BMat.h>

namespace cv {
    /**
     * BMat that contains unsigned greyscale integer pixels
     */
    struct G_xU_BMat : public G_xU_xS_BMat {
        using G_xU_xS_BMat::G_xU_xS_BMat;
    };
}



