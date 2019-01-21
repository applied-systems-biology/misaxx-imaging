//
// Created by rgerst on 25.07.18.
//


#pragma once

#include <misaxx/imaging/coixx/objects/label_properties.h>

namespace coixx {

    /**
     * Object property that finds the centroid of the object
     */
    struct label_pixel_count {
        template<class C, class Void = void> struct type : public label_property {
            int pixels = 0;

            inline void update(int x, int y, const C &value) {
                ++pixels;
            }
        };
    };
}