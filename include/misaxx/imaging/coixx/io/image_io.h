//
// Created by rgerst on 21.03.18.
//


#pragma once

#include <misaxx/imaging/coixx/image.h>
#include <misaxx/imaging/coixx/io/tiff_reader.h>
#include <misaxx/imaging/coixx/io/tiff_writer.h>
#include <boost/filesystem.hpp>
#include <unordered_set>

namespace coixx::io {

    /**
     * Path provided in save() and load() functions
     */
    using path = boost::filesystem::path;

    /**
     * Contains all supported file extensions
     */
    const std::unordered_set<std::string> supported_file_extensions = { ".png",".jpg",".jpeg",".bmp",".PNG",".JPG",".JPEG",".BMP",".tif",".TIFF",".tiff",".TIF" };

    /**
     * Contains all file types
     */
    enum class file_type {
        unsupported,
        png,
        jpg,
        tiff,
        bmp
    };

    /**
     * Identifies the file_type of a file
     * @param t_filename
     * @return
     */
    inline file_type identify(const boost::filesystem::path &t_filename) {
        const auto extension = boost::filesystem::extension(t_filename);

        if(extension == ".tiff" || extension == ".TIFF" || extension == ".tif" || extension == ".tiff")
            return file_type ::tiff;
        else if(extension == ".png" || extension == ".PNG")
            return file_type::png;
        else if(extension == ".bmp" || extension == ".BMP")
            return file_type ::bmp;
        else if(extension == ".jpg" || extension == ".JPG" || extension == ".JPEG" || extension == ".jpg")
            return file_type ::jpg;
        else
            return file_type ::unsupported;
    }

    /**
     * Contains a function save(image, path) and a function load(path)
     * @tparam C
     */
    template<class C> struct image_io {

    };

    /**
     * image_io specialization that loads & saves images::grayscale8u and images::mask
     */
    template<> struct image_io<colors::grayscale8u > {
        static void save(const images::grayscale8u &t_img, const path& t_filename) {
            // We can use OpenCV's native save feature
            cv::imwrite(t_filename.string(), t_img.get_image());
        }

        static images::grayscale8u load(const path& t_filename) {
            images::raw img = cv::imread(t_filename.string(), cv::IMREAD_GRAYSCALE);
            if(img.empty()) {
                throw std::runtime_error("Could not load image " + t_filename.string());
            }

            return images::grayscale8u(std::move(img));
        }
    };

    /**
     * image_io specialization that loads & saves images::grayscale16u
     */
    template<> struct image_io<colors::grayscale16u > {
        static void save(const images::grayscale16u &t_img, const path& t_filename) {
            // We can use OpenCV's native save feature
            cv::imwrite(t_filename.string(), t_img.get_image());
        }

        static images::grayscale16u load(const path& t_filename) {
            images::raw img = cv::imread(t_filename.string(), cv::IMREAD_GRAYSCALE | cv::IMREAD_ANYDEPTH);

            if(img.empty()) {
                throw std::runtime_error("Could not load image " + t_filename.string());
            }
            if(img.type() != CV_16U) {
                throw std::runtime_error("The image has the wrong depth!");
            }

            return images::grayscale16u(std::move(img));
        }
    };

    /**
     * image_io specialization that loads & saves images::bgr8u
     */
    template<> struct image_io<colors::bgr8u > {
        static void save(const images::bgr8u &t_img, const path& t_filename) {
            // We can use OpenCV's native save feature
            cv::imwrite(t_filename.string(), t_img.get_image());
        }

        static images::bgr8u load(const path& t_filename) {
            images::raw img = cv::imread(t_filename.string(), cv::IMREAD_COLOR);

            if(img.empty()) {
                throw std::runtime_error("Could not load image " + t_filename.string());
            }

            return images::bgr8u(std::move(img));
        }
    };

    /**
     * image_io specialization that loads & saves images::grayscale32s and images::labels32s, images::labels
     */
    template<> struct image_io<colors::grayscale32s > {
        static void save(const images::grayscale32s &t_img, const path& t_filename) {
            if(identify(t_filename) != file_type::tiff) {
                throw std::runtime_error("Only TIFF files are supported!");
            }

            tiff_writer tif(t_filename.string(), t_img.get_size(), 1, 32, 2); // SAMPLEFORMAT_INT = 2

            for (int y = 0; y < t_img.get_image().rows; ++y)
            {
                const colors::grayscale32s *row = t_img.row_ptr(y);
                tif.write_row(row, static_cast<unsigned int>(y));
            }
        }

        static images::grayscale32s load(const path& t_filename) {
            if(identify(t_filename) != file_type::tiff) {
                throw std::runtime_error("Only TIFF files are supported!");
            }

            tiff_reader tif(t_filename.string());

            if(tif.get_num_samples() != 1 || tif.get_sample_format() != 2 || tif.get_depth() != 32) { // SAMPLEFORMAT_INT = 2
                throw std::runtime_error("Input file " + t_filename.string() + " cannot be read as int32 TIFF image!");
            }

            images::grayscale32s result(tif.get_size(), colors::grayscale32s::background());
            const auto image_height = tif.get_image_height();

            for (unsigned int y = 0; y < image_height; ++y)
            {
                auto *row = result.get_image().ptr<float>(static_cast<int>(y));
                tif.read_row(row, y);
            }

            return result;
        }
    };

    /**
     * image_io specialization that loads & saves images::grayscale_float
     */
    template<> struct image_io<colors::grayscale_float > {
        static void save(const images::grayscale_float &t_img, const path& t_filename) {
            if(identify(t_filename) != file_type::tiff) {
                throw std::runtime_error("Only TIFF files are supported!");
            }

            tiff_writer tif(t_filename.string(), t_img.get_size(), 1, 32, 3); // SAMPLEFORMAT_IEEEFP = 3

            for (int y = 0; y < t_img.get_image().rows; ++y)
            {
                const colors::grayscale32f *row =t_img.row_ptr(y);
                tif.write_row(row, static_cast<unsigned int>(y));
            }
        }

        static images::grayscale_float load(const path& t_filename) {
            if(identify(t_filename) != file_type::tiff) {
                throw std::runtime_error("Only TIFF files are supported!");
            }

            tiff_reader tif(t_filename.string());

            if(tif.get_num_samples() != 1 || tif.get_sample_format() != 3 || tif.get_depth() != 32) { // SAMPLEFORMAT_IEEEFP = 3
                throw std::runtime_error("Input file " + t_filename.string() + " cannot be read as float TIFF image!");
            }

            images::grayscale_float result(tif.get_size(), colors::grayscale_float::black());
            const auto image_height = tif.get_image_height();

            for (unsigned int y = 0; y < image_height; ++y)
            {
                auto *row = result.get_image().ptr<float>(static_cast<int>(y));
                tif.read_row(row, y);
            }

            return result;
        }
    };
}