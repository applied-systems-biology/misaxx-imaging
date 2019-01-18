//
// Created by rgerst on 17.12.18.
//


#pragma once

#include <misaxx-imaging/coixx/objects/label_properties.h>

namespace coixx {

    /**
    * Object property that contains no information
    */
    struct label_dummy_property {
        template<class C, class Void = void>
        struct type : public label_property {
            inline void update(int x, int y, const C &value) {
            }
        };
    };

}