//
// Created by rgerst on 03.12.18.
//


#pragma once

#include <vector>
#include <opencv2/opencv.hpp>

namespace coixx::toolbox::channels {

    /**
     * Splits the channels into single-channel images of given type
     * @tparam DestinationImage Must match the input image types
     * @param t_target
     * @return
     */
    template<class DestinationImage> auto split(std::vector<DestinationImage> &t_target) {
        static_assert(DestinationImage::color_type::channels == 1, "The destination type must have exactly 1 channel!");
        return [&t_target](auto t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            static_assert(std::is_same<typename DestinationImage::color_type::channel_type, typename image_t::color_type::channel_type>::value, "The channel types must match!");

            const cv::Mat &raw = t_img.get_image();
            std::vector<cv::Mat> target(raw.channels());
            cv::split(raw, target.data());

            for(auto &v : target) {
                t_target.emplace_back(DestinationImage(v));
            }
        };
    }

    /**
     * Merges the channels into the output image
     * @tparam OutputImage
     * @tparam InputImage
     * @param t_input
     * @return
     */
    template<class OutputImage, class InputImage> inline OutputImage merge_vector(const std::vector<InputImage> &t_input) {
        static_assert(InputImage::color_type::channels == 1, "The input images must have 1 channel");
        static_assert(std::is_same<typename OutputImage::color_type::channel_type, typename InputImage::color_type::channel_type>::value, "The channel types must match!");

        if(t_input.size() != OutputImage::color_type::channels)
            throw std::runtime_error("The number of input input images does not match the number of channels in the output");

        std::vector<cv::Mat> input;
        for(const auto &v : t_input) {
            input.push_back(v.get_image());
        }
        cv::Mat result;
        cv::merge(input, result);

        return OutputImage(result);
    }

    namespace detail {
        template<class OutputImage, class InputImage, class... Args> inline void merge_detail( std::vector<cv::Mat> &result, const InputImage &img, const Args& ...args) {
            static_assert(InputImage::color_type::channels == 1, "The input images must have 1 channel");
            static_assert(std::is_same<typename OutputImage::color_type::channel_type, typename InputImage::color_type::channel_type>::value, "The channel types must match!");

            result.push_back(img.get_image());

            if constexpr (sizeof...(Args) != 0) {
                merge_detail<OutputImage>(result, args...);
            }
        }
    }


    /**
    * Merges the channels into the output image
    * @tparam OutputImage
    * @tparam InputImages Input images
    * @param t_input
    * @return
    */
    template<class OutputImage, class... InputImages> inline OutputImage merge(const InputImages& ...args) {

        static_assert(sizeof...(InputImages) == OutputImage::color_type::channels, "The number of input images must match the number of channels!");
        std::vector<cv::Mat> input;
        detail::merge_detail<OutputImage>(input, args...);
        cv::Mat result;
        cv::merge(input, result);

        return OutputImage(result);
    }

}