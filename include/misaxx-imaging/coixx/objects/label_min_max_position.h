//
// Created by rgerst on 25.07.18.
//


#pragma once

#include <misaxx-imaging/coixx/objects/label_properties.h>

namespace coixx {

    /**
     * Object property that contains minimum and maximum x and y values
     */
    struct label_min_max_position {
        template<class C, class Void = void> struct type : public label_property {
            int min_x = std::numeric_limits<int>::max();
            int max_x = std::numeric_limits<int>::min();
            int min_y = std::numeric_limits<int>::max();
            int max_y = std::numeric_limits<int>::min();

            inline void update(int x, int y, const C &value) {
                min_x = std::min(x, min_x);
                max_x = std::max(x, max_x);
                min_y = std::min(y, min_y);
                max_y = std::max(y, max_y);
            }

            int get_width() const {
                return max_x - min_x + 1;
            }

            int get_height() const {
                return max_y - min_y + 1;
            }

            cv::Point get_center() const {
                return cv::Point(min_x + (max_x - min_x) / 2, min_y + (max_y - min_y) / 2);
            }
        };
    };
}