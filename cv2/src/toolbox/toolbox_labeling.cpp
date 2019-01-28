//
// Created by rgerst on 28.01.19.
//

#include "misaxx/imaging/utils/cv2/toolbox/toolbox_labeling.h"

cv::images::labels
cv::toolbox::labeling::connected_components(const cv::images::mask &img, cv::connectivity connectivity) {
    cv::images::labels result;
    cv::connectedComponents(img, result, static_cast<int>(connectivity), CV_32S);
    return result;
}
