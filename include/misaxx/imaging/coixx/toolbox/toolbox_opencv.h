//
// Created by rgerst on 04.12.18.
//


#pragma once
#include <opencv2/opencv.hpp>

namespace coixx::toolbox::opencv {

    /**
     * Converts the input OpenCV image into the target coi++ image. If the image type of the OpenCV image does
     * not match the target type, semantic conversion will be applied
     * @tparam ImageDst
     * @param t_mat
     * @return
     */
    template<class ImageDst> inline ImageDst semantic_from_grayscale(const cv::Mat &t_mat) {

        double opencv_min = 0;
        double opencv_max = 0;
        const double dst_min = ImageDst::color_type::first_value;
        const double dst_max = ImageDst::color_type::last_value;

        switch(t_mat.type()) {
            case CV_8U: {
                if(std::is_same<typename ImageDst::color_type::channel_type, uchar>::value) {
                    return ImageDst(t_mat);
                }
                opencv_min = std::numeric_limits<uchar>::lowest();
                opencv_max = std::numeric_limits<uchar>::max();
            }
            break;
            case CV_8S: {
                if(std::is_same<typename ImageDst::color_type::channel_type, char>::value) {
                    return ImageDst(t_mat);
                }
                opencv_min = std::numeric_limits<char>::lowest();
                opencv_max = std::numeric_limits<char>::max();
            }
            break;
            case CV_16U: {
                if(std::is_same<typename ImageDst::color_type::channel_type, ushort>::value) {
                    return ImageDst(t_mat);
                }
                opencv_min = std::numeric_limits<ushort>::lowest();
                opencv_max = std::numeric_limits<ushort>::max();
            }
            break;
            case CV_16S: {
                if(std::is_same<typename ImageDst::color_type::channel_type, short>::value) {
                    return ImageDst(t_mat);
                }
                opencv_min = std::numeric_limits<short>::lowest();
                opencv_max = std::numeric_limits<short>::max();
            }
            break;
            case CV_32S: {
                if(std::is_same<typename ImageDst::color_type::channel_type, int>::value) {
                    return ImageDst(t_mat);
                }
                opencv_min = std::numeric_limits<int>::lowest();
                opencv_max = std::numeric_limits<int>::max();
            }
            break;
            case CV_32F: {
                if(std::is_same<typename ImageDst::color_type::channel_type, float>::value) {
                    return ImageDst(t_mat);
                }
                opencv_min = std::numeric_limits<float>::lowest();
                opencv_max = std::numeric_limits<float>::max();
            }
            break;
            case CV_64F: {
                if(std::is_same<typename ImageDst::color_type::channel_type, double>::value) {
                    return ImageDst(t_mat);
                }
                opencv_min = std::numeric_limits<double>::lowest();
                opencv_max = std::numeric_limits<double>::max();
            }
            break;
            default:
                throw std::runtime_error("Unsupported OpenCV type!");
        }

        // Semantic convert
        double scale_factor = (dst_max - dst_min) * 1.0 / (opencv_max - opencv_min);
        cv::Mat result;
        t_mat.convertTo(result, ImageDst::opencv_type, scale_factor);
        return ImageDst(std::move(result));
    }

    /**
     * Wraps ImageDst around the input if it is a multi-channel image, otherwise
     * returns semantic_from_grayscale
     * @tparam ImageDst
     * @param t_mat
     * @return
     */
    template<class ImageDst> inline ImageDst semantic_from(const cv::Mat &t_mat) {
        if constexpr (ImageDst::color_type::channels == 1) {
            return semantic_from_grayscale<ImageDst>(t_mat);
        }
        else {
            return ImageDst(t_mat);
        }
    }

}