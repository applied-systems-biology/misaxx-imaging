//
// Created by rgerst on 28.01.19.
//

#pragma once

#include <opencv2/core/mat.hpp>

namespace cv::toolbox {

    template<class Recoloring> inline void recolor(const cv::Mat &src, cv::Mat &dst, const Recoloring &function) {
        if(dst.empty()) {
            throw std::runtime_error("Destination image must be initialized!");
        }
        using T = typename Recoloring::input_type;
        using U = typename Recoloring::output_type;
        for(int y = 0; y < src.rows; ++y) {
            const T*src_row = src.ptr<T>(y);
            T *dst_row = dst.ptr<U>(y);
            for(int x = 0; x < src.cols; ++x) {
                dst_row[x] = function.recolor(src_row[x]);
            }
        }
    }

    template<class Recoloring> inline void recolor(cv::Mat &img, const Recoloring function) {
        using T = typename Recoloring::input_type;
        static_assert(std::is_same<typename Recoloring::input_type, typename Recoloring::output_type>::value,
                "Recoloring must recolor within the same color space!");
        for(int y = 0; y < img.rows; ++y) {
            T *row = img.ptr<T>(y);
            for(int x = 0; x < img.cols; ++x) {
                row[x] = function.recolor(row[x]);
            }
        }
    }

}


