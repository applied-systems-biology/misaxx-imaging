//
// Created by rgerst on 25.07.18.
//


#pragma once

#include <misaxx/imaging/coixx/objects/object_properties.h>

namespace coixx {

    /**
     * Image object property that contains minimum and maximum value and the number of non-zero pixels
     */
    struct object_pixel_stats {
        template<class CImage, class CLabel> struct type : public object_property {

            using image_raw_color_type = CImage;

            int nonzero_pixels = 0;
            image_raw_color_type min_value = std::numeric_limits<image_raw_color_type >::max();
            image_raw_color_type max_value = std::numeric_limits<image_raw_color_type >::min();

            inline void update(int x, int y, CLabel label, CImage value) {
                if(value != 0)
                    ++nonzero_pixels;
                min_value = std::min(min_value, value);
                max_value = std::max(max_value, value);
            }
        };
    };

}