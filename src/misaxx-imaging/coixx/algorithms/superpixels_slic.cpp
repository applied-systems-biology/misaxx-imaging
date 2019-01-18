//
// Created by ruman on 17.12.18.
//

#include <misaxx-imaging/coixx/algorithms/superpixels_slic.h>

using namespace coixx;

superpixels_slic::superpixels_slic(const cv::Mat &t_img, superpixels_slic_algorithm t_algorithm, int t_region_size,
                                   float t_compactness) :
        m_size(cv::Size(t_img.rows, t_img.cols)),
        m_algorithm(t_algorithm),
        m_region_size(t_region_size),
        m_compactness(t_compactness),
        m_instance(cv::ximgproc::createSuperpixelSLIC(t_img, static_cast<int>(t_algorithm),
                                                      t_region_size, t_compactness)) {

}

cv::ximgproc::SuperpixelSLIC &superpixels_slic::get_instance() {
    return *m_instance;
}

const cv::ximgproc::SuperpixelSLIC &superpixels_slic::get_instance() const {
    return *m_instance;
}

images::mask superpixels_slic::to_mask(bool t_thick_line) const {
    images::mask target = images::mask::allocate(m_size);
    m_instance->getLabelContourMask(target.get_image(), t_thick_line);
    return target;
}

images::grayscale32s superpixels_slic::get_labels() const {
    images::grayscale32s target = images::labels::allocate(m_size);
    m_instance->getLabels(target.get_image());
    return target;
}

void superpixels_slic::merge_small_components(int t_min_element_size) const {
    m_instance->enforceLabelConnectivity(t_min_element_size);
}

int superpixels_slic::get_num_superpixels() const {
    return m_instance->getNumberOfSuperpixels();
}

void superpixels_slic::iterate(int t_num_iterations) const {
    m_instance->iterate(t_num_iterations);
}

