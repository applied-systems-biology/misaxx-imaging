//
// Created by rgerst on 28.01.19.
//

#include <misaxx/imaging/utils/cv2/toolbox/toolbox_normalize.h>

#include "misaxx/imaging/utils/cv2/toolbox/toolbox_normalize.h"
#include <misaxx/imaging/utils/cv2/toolbox/toolbox_normalize.h>
#include <misaxx/imaging/utils/cv2/toolbox/toolbox_statistics.h>

void cv::toolbox::normalize::by_max(cv::images::grayscale32f &img) {
    double max = cv::toolbox::statistics::min_max_loc(img).max.value;
    img.self() /= max;
}
