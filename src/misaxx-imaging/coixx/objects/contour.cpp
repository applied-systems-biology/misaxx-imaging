//
// Created by ruman on 17.12.18.
//

#include <misaxx-imaging/coixx/objects/contour.h>

using namespace coixx;

contour::contour(const images::mask &t_img, contour::return_mode t_return_mode, contour::approximation t_approx) {
    images::mask cont = t_img.clone();
    cv::findContours(cont.get_image(), m_contours, m_hierarchy, static_cast<int>(t_return_mode), static_cast<int>(t_approx));
}

const std::vector<std::vector<cv::Point> > &contour::get_contours() const {
    return m_contours;
}

const std::vector<cv::Vec4i> &contour::get_hierarchy() const {
    return m_hierarchy;
}
