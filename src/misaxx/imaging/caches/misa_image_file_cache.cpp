#include <misaxx/imaging/caches/misa_image_file_cache.h>

cv::Mat &misaxx::imaging::misa_image_file_cache::get() {
    return m_value;
}

const cv::Mat &misaxx::imaging::misa_image_file_cache::get() const {
    return m_value;
}

void misaxx::imaging::misa_image_file_cache::set(cv::Mat value) {
    m_value = std::move(value);
}

bool misaxx::imaging::misa_image_file_cache::has() const {
    return !m_value.empty();
}

bool misaxx::imaging::misa_image_file_cache::can_pull() const {
    return boost::filesystem::is_regular_file(m_path);
}

void misaxx::imaging::misa_image_file_cache::pull() {
    m_value = cv::imread(m_path.string(), cv::IMREAD_UNCHANGED);
}

void misaxx::imaging::misa_image_file_cache::stash() {
    m_value.release();
}

void misaxx::imaging::misa_image_file_cache::push() {
    cv::imwrite(m_path.string(), m_value);
}

void misaxx::imaging::misa_image_file_cache::do_link(const misaxx::imaging::misa_image_description &t_description) {
    if(t_description.filename.empty())
        throw std::runtime_error("Cannot link to file description with empty file name!");
    m_path = this->get_location() / t_description.filename;
    this->set_unique_location(m_path);
}

misaxx::imaging::misa_image_description
misaxx::imaging::misa_image_file_cache::produce_description(const boost::filesystem::path &t_location,
                                                            const misaxx::imaging::misa_image_pattern &t_pattern) {
    auto image = t_pattern.produce(t_location);
    misa_image_description result;
    result.filename = std::move(image.filename);
    return result;
}
