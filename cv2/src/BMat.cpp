//
// Created by rgerst on 25.01.19.
//

#include <misaxx/imaging/utils/cv2/BMat.h>

cv::BMat::BMat(cv::Mat mat) : cv::Mat(std::move(mat)) {
}

cv::BMat::BMat(const cv::Size &size, int type, const cv::Scalar &init) : cv::Mat(size, type, init) {

}

void cv::BMat::swap() {
    std::swap(self(), buffer(true));
}

cv::Mat &cv::BMat::buffer(bool nonEmpty) {
    if(nonEmpty && m_buffer.empty()) {
        m_buffer = cv::Mat(rows, cols, type());
    }
    return m_buffer;
}

cv::BMat cv::BMat::allocate(const cv::Size &size, int type) {
    return cv::BMat(cv::Mat(size, type));
}

cv::Mat &cv::BMat::self() {
    return *this;
}




