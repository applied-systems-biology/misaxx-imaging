//
// Created by rgerst on 29.01.19.
//


#pragma once

namespace cv::toolbox {
    template<class _BMat>
    cv::images::mask cv::toolbox::to_mask(const _BMat &img) {
        auto result = cv::images::mask::allocate(img.size());
        for(int y = 0; y < img.rows; ++y) {
            const auto *src_row = img[y];
            uchar *dst_row = result[y];
            for(int x = 0; x < img.cols; ++x) {
                if(src_row[x] > 0) {
                    dst_row[x] = 255;
                }
                else {
                    dst_row[x] = 0;
                }
            }
        }
        return result;
    }

    uchar otsu(images::mask &img) {
        uchar threshold = static_cast<uchar>(cv::threshold(img, img.buffer(), 0, 255, cv::THRESH_OTSU));
        img.swap();
        return threshold;
    }
}