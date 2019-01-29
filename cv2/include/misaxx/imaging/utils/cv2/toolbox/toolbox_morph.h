//
// Created by rgerst on 28.01.19.
//

#pragma once


#include <misaxx/imaging/utils/cv2/ReadableBMatTypes.h>

namespace cv::toolbox::morph {

    extern void dilate(images::grayscale8u &img, const images::mask &kernel, int iterations = 1);

    extern void erode(images::grayscale8u &img, const images::mask &kernel, int iterations = 1);

    extern void open(images::grayscale8u &img, const images::mask &kernel, int iterations = 1);

    extern void close(images::grayscale8u &img, const images::mask &kernel, int iterations = 1);

    extern void gradient(images::grayscale8u &img, const images::mask &kernel, int iterations = 1);

    extern void tophat(images::grayscale8u &img, const images::mask &kernel, int iterations = 1);

    extern void blackhat(images::grayscale8u &img, const images::mask &kernel, int iterations = 1);

    extern void hitmiss(images::grayscale8u &img, const images::mask &kernel, int iterations = 1);

    extern void dilate(images::grayscale16u &img, const images::mask &kernel, int iterations = 1);

    extern void erode(images::grayscale16u &img, const images::mask &kernel, int iterations = 1);

    extern void open(images::grayscale16u &img, const images::mask &kernel, int iterations = 1);

    extern void close(images::grayscale16u &img, const images::mask &kernel, int iterations = 1);

    extern void gradient(images::grayscale16u &img, const images::mask &kernel, int iterations = 1);

    extern void tophat(images::grayscale16u &img, const images::mask &kernel, int iterations = 1);

    extern void blackhat(images::grayscale16u &img, const images::mask &kernel, int iterations = 1);

    extern void hitmiss(images::grayscale16u &img, const images::mask &kernel, int iterations = 1);

    extern void dilate(images::grayscale16s &img, const images::mask &kernel, int iterations = 1);

    extern void erode(images::grayscale16s &img, const images::mask &kernel, int iterations = 1);

    extern void open(images::grayscale16s &img, const images::mask &kernel, int iterations = 1);

    extern void close(images::grayscale16s &img, const images::mask &kernel, int iterations = 1);

    extern void gradient(images::grayscale16s &img, const images::mask &kernel, int iterations = 1);

    extern void tophat(images::grayscale16s &img, const images::mask &kernel, int iterations = 1);

    extern void blackhat(images::grayscale16s &img, const images::mask &kernel, int iterations = 1);

    extern void hitmiss(images::grayscale16s &img, const images::mask &kernel, int iterations = 1);

    extern void dilate(images::grayscale32f &img, const images::mask &kernel, int iterations = 1);

    extern void erode(images::grayscale32f &img, const images::mask &kernel, int iterations = 1);

    extern void open(images::grayscale32f &img, const images::mask &kernel, int iterations = 1);

    extern void close(images::grayscale32f &img, const images::mask &kernel, int iterations = 1);

    extern void gradient(images::grayscale32f &img, const images::mask &kernel, int iterations = 1);

    extern void tophat(images::grayscale32f &img, const images::mask &kernel, int iterations = 1);

    extern void blackhat(images::grayscale32f &img, const images::mask &kernel, int iterations = 1);

    extern void hitmiss(images::grayscale32f &img, const images::mask &kernel, int iterations = 1);

    extern void dilate(images::grayscale64f &img, const images::mask &kernel, int iterations = 1);

    extern void erode(images::grayscale64f &img, const images::mask &kernel, int iterations = 1);

    extern void open(images::grayscale64f &img, const images::mask &kernel, int iterations = 1);

    extern void close(images::grayscale64f &img, const images::mask &kernel, int iterations = 1);

    extern void gradient(images::grayscale64f &img, const images::mask &kernel, int iterations = 1);

    extern void tophat(images::grayscale64f &img, const images::mask &kernel, int iterations = 1);

    extern void blackhat(images::grayscale64f &img, const images::mask &kernel, int iterations = 1);

    extern void hitmiss(images::grayscale64f &img, const images::mask &kernel, int iterations = 1);

    extern void close_holes(images::grayscale8u &img, const images::mask &kernel);

    extern void close_holes(images::grayscale16u &img, const images::mask &kernel);

    extern void close_holes(images::grayscale32f &img, const images::mask &kernel);

    extern void close_holes(images::grayscale64f &img, const images::mask &kernel);

}


