//
// Created by rgerst on 28.01.19.
//


#pragma once

#include <misaxx/imaging/utils/cv2/BMat.h>

namespace cv {

    /**
     * Union of various static Mat types
     * @tparam _Mats
     */
    template<class ..._Mats> struct UnionSMat : public BMat {
        using BMat::BMat;
    };

}