//
// Created by rgerst on 28.01.19.
//

#include <misaxx/imaging/utils/cv2/toolbox/toolbox_blur.h>

#include "misaxx/imaging/utils/cv2/toolbox/toolbox_blur.h"

void cv::toolbox::blur::median(cv::images::grayscale &img, int ksize) {
    cv::medianBlur(img, img.buffer(true), ksize);
    img.swap();
}

void cv::toolbox::blur::gauss(cv::images::grayscale &img, double sigmax, double sigmay) {
    cv::GaussianBlur(img, img.buffer(true), cv::Size(0, 0), sigmax, sigmay);
    img.swap();
}

void cv::toolbox::blur::gauss(cv::images::grayscale &img, double sigmaxy) {
    gauss(img, sigmaxy, sigmaxy);
}

