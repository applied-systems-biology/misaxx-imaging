//
// Created by rgerst on 28.01.19.
//


#pragma once
#include <cstddef>

namespace cv {
    struct cc_average_intensity {
        double sum = 0;
        size_t count = 0;

        void update(int x, int y, int label);

        void update(int x, int y, int label, double value);

        double avg() const;
    };
}
