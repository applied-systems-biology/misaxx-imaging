//
// Created by rgerst on 25.07.18.
//


#pragma once

#include <misaxx-imaging/coixx/objects/object_properties.h>
#include <misaxx-imaging/coixx/histogram.h>

namespace coixx {

    /**
    * Calculates a histogram of the object value
    * @tparam MapTypeLabel
    */
    struct object_histogram {

        template<class CImage, class CLabel> struct type : public object_property {

            using image_raw_color_type = CImage;

            hashmap_histogram<CImage> histogram;

            inline void update(int x, int y, CLabel label, CImage value) {
                histogram.count(value);
            }
        };

    };

}