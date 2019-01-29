//
// Created by rgerst on 29.01.19.
//


#pragma once

namespace cv {
    template<typename _Tp>
    BMat_<_Tp>::BMat_(const cv::Size &size, const _Tp &init) : BMat(size, cv::traits::Type<_Tp>::value, init) {
    }

    template<typename _Tp>
    BMat_<_Tp>::BMat_(const cv::Mat &mat) : BMat(mat) {
        if(type() != cv::traits::Type<_Tp>::value)
            throw std::runtime_error("Tried to initialize static cv::BMat from cv::Mat with incompatible type!");
    }

    template<typename _Tp>
    BMat_<_Tp> BMat_<_Tp>::allocate(const cv::Size &size) {
        return cv::BMat_<_Tp>(cv::Mat(size, cv::traits::Type<_Tp>::value));
    }

    template<typename _Tp>
    _Tp *BMat_<_Tp>::operator[](int y) {
        return ptr<_Tp>(y);
    }

    template<typename _Tp>
    const _Tp *BMat_<_Tp>::operator[](int y) const {
        return ptr<_Tp>(y);
    }

    template<typename _Tp>
    BMat_ <_Tp> BMat_<_Tp>::clone() const {
        return BMat_<_Tp>(cv::BMat::clone());
    }
}
