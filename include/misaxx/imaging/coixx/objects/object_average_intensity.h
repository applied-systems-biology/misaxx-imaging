//
// Created by rgerst on 05.09.18.
//


#pragma once

#include <misaxx/imaging/coixx/objects/object_properties.h>

namespace coixx {

    /**
     * Image object property that contains the average intensity
     */
    struct object_average_intensity {
        template<class CImage, class CLabel> struct type : public object_property {

            using image_raw_color_type = CImage;

            int pixels = 0;
            double intensity_sum = 0;

            double average_intensity() const {
                return intensity_sum / pixels;
            }

            inline void update(int x, int y, CLabel label, CImage value) {
                ++pixels;
                intensity_sum += value;
            }
        };
    };

}