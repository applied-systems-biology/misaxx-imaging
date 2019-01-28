//
// Created by rgerst on 28.01.19.
//

#include <misaxx/imaging/utils/cv2/label_properties/cc_average_intensity.h>

#include "misaxx/imaging/utils/cv2/label_properties/cc_average_intensity.h"

void cv::cc_average_intensity::update(int , int , int , double value) {
    ++count;
    sum += value;
}

void cv::cc_average_intensity::update(int , int , int) {
    ++count;
}

double cv::cc_average_intensity::avg() const {
    return sum / count;
}

