//
// Created by rgerst on 28.01.19.
//

#pragma once

namespace cv::toolbox {

    /**
     * Applies a filter to a BMat. The BMat will be swapped after the function is executed
     * @tparam _BMat
     * @tparam _Func Function that takes the image as argument
     * @param img
     * @param function
     */
    template<class _BMat, class _Func> void apply(_BMat &img, const _Func &function) {
        function(img);
        img.swap();
    }

    /**
     * Processes an image and returns the result of the function
     * @tparam _Mat
     * @tparam _Func Function that takes the image as argument
     * @param img
     * @param function
     * @return
     */
    template<class _Mat, class _Func> auto process(_Mat &img, const _Func &function) {
        return function(img);
    }

    /**
     * Processes an image and returns the result of the function
     * @tparam _Mat
     * @tparam _Func Function that takes the image as argument
     * @param img
     * @param function
     * @return
     */
    template<class _Mat, class _Func> auto process(const _Mat &img, const _Func &function) {
        return function(img);
    }

}


