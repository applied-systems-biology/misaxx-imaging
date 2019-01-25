//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/BMat.h>

namespace cv {
    /**
     * BMat that contains greyscale pixels
     */
    struct G_BMat : public BMat {
        using BMat::BMat;
    };
}



