//
// Created by rgerst on 04.12.18.
//

#include <tiffio.h>
#include <misaxx-imaging/coixx/io/tiff_writer.h>
#include <tiff.h>
#include <tiffio.h>

coixx::io::tiff_writer::tiff_writer(const std::string &t_filename, const cv::Size &t_image_size, uint16 t_num_samples,
                                    uint16 t_depth, uint16 t_sample_format) : m_tiff(TIFFOpen(t_filename.c_str(), "w")) {
    TIFFSetField(m_tiff, TIFFTAG_IMAGEWIDTH, static_cast<uint32>(t_image_size.width));  // set the width of the image
    TIFFSetField(m_tiff, TIFFTAG_IMAGELENGTH, static_cast<uint32>(t_image_size.height));    // set the height of the image
    TIFFSetField(m_tiff, TIFFTAG_BITSPERSAMPLE, t_depth);
    TIFFSetField(m_tiff, TIFFTAG_SAMPLESPERPIXEL, t_num_samples);
    TIFFSetField(m_tiff, TIFFTAG_SAMPLEFORMAT, t_sample_format);
}

coixx::io::tiff_writer::~tiff_writer() {
    TIFFClose(m_tiff);
}

void coixx::io::tiff_writer::write_row_(const void *row, unsigned int y, unsigned short sample) {
    TIFFWriteScanline(m_tiff, const_cast<void*>(row), y, sample);
}
