//
// Created by rgerst on 24.01.19.
//


#pragma once

#include <misaxx/imaging/coixx/image.h>

namespace coixx {
    /**
     * Wrapper around coixx::image that provides interfaces for buffering
     * @tparam Image
     */
    template<class Image>
    struct buffer {
    public:
        explicit buffer(Image t_image) : m_image(t_image.share()) {
            if(m_image.get_buffer_mat().empty()) {
                m_image.get_buffer_mat() = cv::Mat(t_image.get_height(), t_image.get_width(), t_image.get_open_cv_type());
            }
            m_buffer = Image(m_image.get_buffer_mat());
        }

        Image &get_image() {
            return m_image;
        }

        const Image &get_image() const {
            return m_image;
        }

        Image &get_buffer() {
            return m_buffer;
        }

        const Image &get_buffer() const {
            return m_buffer;
        }

        void swap() {
            std::swap(m_image.get_mat(), m_image.get_buffer_mat());
            m_buffer = Image(m_image.get_buffer_mat());
        }

    private:
        Image m_image;
        Image m_buffer;
    };
}
