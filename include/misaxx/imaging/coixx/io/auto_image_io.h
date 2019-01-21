//
// Created by rgerst on 25.07.18.
//


#pragma once

#include <misaxx/imaging/coixx/converters/semantic_convert.h>
#include <misaxx/imaging/coixx/converters/hard_convert.h>
#include <misaxx/imaging/coixx/io/image_io.h>

namespace coixx::io {

    /**
     * Serializer that loads the image and auto-detects its type.
     * The applies semantic_convert or hard_convert
     * @tparam C
     */
    template<class C> struct auto_image_io {
        static_assert(!std::is_same<C, colors::grayscale32s >::value, "OpenCV cannot natively load colors::grayscale32s!");

        static image<C> load(const path& t_filename) {
            if constexpr (std::is_same<image<C>, images::grayscale8u>::value) {
                images::raw img = cv::imread(t_filename.string(), cv::IMREAD_GRAYSCALE);

                if(img.empty()) {
                    throw std::runtime_error("Could not load image " + t_filename.string());
                }

                return images::grayscale8u(img);
            }
            else if constexpr (std::is_same<image<C>, images::grayscale_float>::value) {
                images::raw img = cv::imread(t_filename.string(), cv::IMREAD_GRAYSCALE | cv::IMREAD_ANYDEPTH);

                if(img.empty()) {
                    throw std::runtime_error("Could not load image " + t_filename.string());
                }

                if(img.depth() == CV_8U) {
                    return converters::semantic_convert<images::grayscale_float> (images::grayscale8u(img));
                }
                else if(img.depth() == CV_16U) {
                    return converters::semantic_convert<images::grayscale_float> (images::grayscale16u(img));
                }
                else {
                    throw std::runtime_error("Unsupported image depth!");
                }
            }
            else if constexpr (std::is_same<image<C>, images::bgr8u >::value) {
                images::raw img = cv::imread(t_filename.string(), cv::IMREAD_COLOR);

                if(img.empty()) {
                    throw std::runtime_error("Could not load image " + t_filename.string());
                }

                return images::bgr8u(img);
            }
            else {
                // Default to specific imageio
                return image_io<C>::load(t_filename);
            }
        }
    };

}