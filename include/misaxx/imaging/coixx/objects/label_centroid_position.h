//
// Created by rgerst on 25.07.18.
//


#pragma once

#include <misaxx/imaging/coixx/objects/label_properties.h>

namespace coixx {

    /**
     * Object property that finds the centroid of the object.
     * Compatible to label_properties and object_properties
     */
    struct label_centroid_position {
        template<class C, class Void = void> struct type : public label_property {
            int pixels = 0;
            unsigned long sum_x = 0;
            unsigned long sum_y = 0;

            inline void update(int x, int y, const C &) {
                ++pixels;
                sum_x += x;
                sum_y += y;
            }

            cv::Point get_centroid() const {
                return cv::Point(sum_x / pixels, sum_y / pixels);
            }
        };
    };

}