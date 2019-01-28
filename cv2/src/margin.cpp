//
// Created by rgerst on 28.01.19.
//

#include "misaxx/imaging/utils/cv2/margin.h"

using namespace cv;

margin::margin(const cv::Rect &t_rect, const cv::Rect &t_containing_rect) : m_left(t_rect.x - t_containing_rect.x),
                                                                            m_top(t_rect.y - t_containing_rect.y),
                                                                            m_right((t_containing_rect.x + t_containing_rect.width) - (t_rect.x + t_rect.width)),
                                                                            m_bottom((t_containing_rect.y + t_containing_rect.height) - (t_rect.y + t_rect.height)) {

}

margin::margin(const cv::Rect &t_rect, const cv::Size &t_size) : margin(t_rect, cv::Rect(0, 0, t_size.width, t_size.height)) {

}

margin::margin(int t_left, int t_top, int t_right, int t_bottom) : m_left(t_left),
                                                                   m_top(t_top),
                                                                   m_right(t_right),
                                                                   m_bottom(t_bottom) {

}

margin::margin(int t_all) : margin(t_all, t_all, t_all, t_all) {

}

margin::margin() : margin(0) {

}

int margin::get_left() const {
    return m_left;
}

int margin::get_top() const {
    return m_top;
}

int margin::get_right() const {
    return m_right;
}

int margin::get_bottom() const {
    return m_bottom;
}

bool margin::is_positive() const {
    return m_left >= 0 && m_top >= 0 && m_right >= 0 && m_bottom >= 0;
}

bool margin::is_negative() const {
    return m_left <= 0 && m_top <= 0 && m_right <= 0 && m_bottom <= 0;
}

margin margin::negate() const {
    return margin(-m_left, -m_top, -m_right, -m_bottom);
}

cv::Rect margin::to_rect(const cv::Rect &t_containing_rect) const {
    return cv::Rect(t_containing_rect.x + m_left, t_containing_rect.y + m_top, t_containing_rect.width - m_right, t_containing_rect.height - m_bottom);
}

cv::Rect margin::to_rect(const cv::Size &t_size) const {
    return to_rect(cv::Rect(0, 0, t_size.width, t_size.height));
}
