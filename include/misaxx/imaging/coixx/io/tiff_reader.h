//
// Created by rgerst on 02.07.18.
//


#pragma once

#include <string>
#include <memory>
#include <opencv2/core/types.hpp>

struct tiff;

namespace coixx::io {

    /**
     * RAII wrapper around libtiff
     */
    class tiff_reader {
    public:

        explicit tiff_reader(const std::string &t_filename);

        ~tiff_reader();

        tiff_reader(const tiff_reader &t_src) = delete;

        tiff &instance() {
            return *m_tiff;
        }

        const tiff &instance() const {
            return *m_tiff;
        }

        unsigned int get_image_height() const;

        unsigned int get_image_width() const;

        unsigned short get_num_samples() const;

        unsigned short get_sample_format() const;

        unsigned short get_depth() const;

        cv::Size get_size() const;

        template<class T> void read_row(T *row_out, unsigned int y) {
            read_row_(row_out, y);
        }

    private:

        tiff *m_tiff;

        void read_row_(void *row_out, unsigned int y);
    };
}

