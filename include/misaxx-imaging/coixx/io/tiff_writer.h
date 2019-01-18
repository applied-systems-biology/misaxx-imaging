//
// Created by rgerst on 02.07.18.
//


#pragma once

#include <memory>
#include <opencv2/core/types.hpp>

struct tiff;

namespace coixx::io {
    class tiff_writer {
    public:

        explicit tiff_writer(const std::string &t_filename, const cv::Size &t_image_size, unsigned short t_num_samples, unsigned short t_depth, unsigned short t_sample_format);

        ~tiff_writer();

        tiff_writer(const tiff_writer &t_src) = delete;

        tiff &instance() {
            return *m_tiff;
        }

        const tiff &instance() const {
            return *m_tiff;
        }

        template<class T> void write_row(const T*row, unsigned int y, unsigned short sample = 0) {
            write_row_(row, y, sample);
        }

    private:

        void write_row_(const void* row, unsigned int y, unsigned short sample = 0);

        tiff *m_tiff;
    };
}