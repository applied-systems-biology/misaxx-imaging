//
// Created by ruman on 17.12.18.
//

#include <misaxx-imaging/coixx/visualizer_gui.h>

using namespace coixx;

save_visualizer_gui::save_visualizer_gui(boost::filesystem::path t_directory) : directory(std::move(t_directory)) {

}

visualizer_gui &visualizer_gui::insert(const images::bgr8u &t_img) {
    insert(input_image<colors::bgr8u>(t_img, "image " + std::to_string(m_images.size() + 1)));
    return *this;
}

visualizer_gui &visualizer_gui::insert(const visualizer_gui::input_image<colors::bgr8u> &t_img) {
    m_images.emplace_back(t_img.image.clone());
    m_image_names.push_back(t_img.name);
    return *this;
}

void visualizer_gui::show_and_wait() {
    window wnd(*this);
    wnd.show_and_wait();
}

void visualizer_gui::save_images(const boost::filesystem::path &t_target_directory, const std::string &t_extension) {

    using namespace coixx::toolbox;

    boost::filesystem::create_directories(t_target_directory);
    for (size_t i = 0; i < m_images.size(); ++i) {
        m_images[i] << save(t_target_directory / (std::to_string(i) + "_" + m_image_names[i] + t_extension));
    }
}

void visualizer_gui::window::on_trackbar_change(int index, void *data) {
    window *wnd = reinterpret_cast<window *>(data);
    wnd->switch_to(static_cast<size_t>(index));
}

visualizer_gui::window::window(visualizer_gui &gui) : m_images(std::move(gui.m_images)), m_image_names(std::move(gui.m_image_names)) {
}

void visualizer_gui::window::switch_to(size_t index) {
    if (index >= m_images.size())
        throw std::runtime_error("Image index out of range!");
    cv::imshow(m_window_name, m_images[index].get_image());
    cv::setWindowTitle(m_window_name, m_image_names[index]);
}

void visualizer_gui::window::show_and_wait() {
    // Generate unique window name. From adress of the object. Very evil.
    unsigned long id = reinterpret_cast<unsigned long>(this);
    m_window_name = std::to_string(id);

    // Create the window
    cv::namedWindow(m_window_name, cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_EXPANDED);
    if (m_images.size() > 1) {
        cv::createTrackbar("Image index", m_window_name, nullptr, static_cast<int>(m_images.size()) - 1, on_trackbar_change, this);
    }

    switch_to(0);

    while (true) {
        int retcode = cv::waitKey(0);
        if (retcode == -1 || retcode == 27)
            return;
    }
}
