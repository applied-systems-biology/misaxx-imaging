//
// Created by rgerst on 04.12.18.
//

#include <tiff.h>
#include <tiffio.h>
#include <misaxx-imaging/coixx/io/tiff_reader.h>

coixx::io::tiff_reader::tiff_reader(const std::string &t_filename) : m_tiff(TIFFOpen(t_filename.c_str(), "r")) {

}

coixx::io::tiff_reader::~tiff_reader() {
    TIFFClose(m_tiff);
}

unsigned int coixx::io::tiff_reader::get_image_height() const {
    uint32 value;
    TIFFGetField(m_tiff, TIFFTAG_IMAGELENGTH, &value);
    return value;
}

unsigned int coixx::io::tiff_reader::get_image_width() const {
    uint32 value;
    TIFFGetField(m_tiff, TIFFTAG_IMAGEWIDTH, &value);
    return value;
}

unsigned short coixx::io::tiff_reader::get_num_samples() const {
    uint16 value;
    TIFFGetField(m_tiff, TIFFTAG_SAMPLESPERPIXEL, &value);
    return value;
}

unsigned short coixx::io::tiff_reader::get_sample_format() const {
    uint16 value;
    TIFFGetField(m_tiff, TIFFTAG_SAMPLEFORMAT, &value);
    return value;
}

unsigned short coixx::io::tiff_reader::get_depth() const {
    uint16 value;
    TIFFGetField(m_tiff, TIFFTAG_BITSPERSAMPLE, &value);
    return value;
}

cv::Size coixx::io::tiff_reader::get_size() const {
    return cv::Size2i(get_image_width(), get_image_height());
}

void coixx::io::tiff_reader::read_row_(void *row_out, unsigned int y) {
    TIFFReadScanline(m_tiff, row_out, y);
}
