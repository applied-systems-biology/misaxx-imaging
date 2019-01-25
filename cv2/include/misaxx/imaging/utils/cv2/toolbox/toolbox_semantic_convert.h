//
// Created by rgerst on 25.01.19.
//

#pragma once
#include <misaxx/imaging/utils/cv2/static_types.h>

namespace cv::toolbox::semantic_convert {

    /**
     * Semantic conversion to images::grayscale8u
     * @param img
     * @return
     */
    extern images::grayscale8u to_grayscale8u(const images::grayscale &img);

    /**
     * Semantic conversion to images::grayscale8s
     * @param img
     * @return
     */
    extern images::grayscale8s to_grayscale8s(const images::grayscale &img);

    /**
    * Semantic conversion to images::grayscale16u
    * @param img
    * @return
    */
    extern images::grayscale16u to_grayscale16u(const images::grayscale &img);

    /**
     * Semantic conversion to images::grayscale16s
     * @param img
     * @return
     */
    extern images::grayscale16s to_grayscale16s(const images::grayscale &img);

    /**
     * Semantic conversion to images::grayscale32f
     * @param img
     * @return
     */
    extern images::grayscale32f to_grayscale32f(const images::grayscale &img);

    /**
     * Semantic conversion to images::grayscale64f
     * @param img
     * @return
     */
    extern images::grayscale64f to_grayscale64f(const images::grayscale &img);
}


