//
// Created by rgerst on 07.02.18.
//


#pragma once

#include <opencv2/opencv.hpp>
#include <misaxx/utils/type_traits.h>

namespace coixx {

    template<class ChannelType, int Channels> inline constexpr int get_opencv_type() {
        if constexpr (std::is_same<ChannelType, uchar>::value) {
            return CV_8UC(Channels);
        }
        else if constexpr (std::is_same<ChannelType, char>::value) {
            return CV_8SC(Channels);
        }
        else if constexpr (std::is_same<ChannelType, ushort>::value) {
            return CV_16UC(Channels);
        }
        else if constexpr (std::is_same<ChannelType, short>::value) {
            return CV_16SC(Channels);
        }
        else if constexpr (std::is_same<ChannelType, int>::value) {
            return CV_32SC(Channels);
        }
        else if constexpr (std::is_same<ChannelType, float>::value) {
            return CV_32FC(Channels);
        }
        else if constexpr (std::is_same<ChannelType, double>::value) {
            return CV_64FC(Channels);
        }
        else {
            static_assert(misaxx::utils::always_false<ChannelType>::value, "Type is not supported by OpenCV!");
        }
    }

    /**
     * Base class for a color. Wraps around a raw color value that is internally stored within the image.
     * To define a color space, the class must inherit from image_color and have following members:
     *
     * static constexpr int opencv_type, which states the internal OpenCV type of the image
     * static constexpr int num_channels, which states the number of channels
     * static const image_color<T> default_value, which states the default value (usually 0/black)
     * static const image_color<T> first_value, which states the lowest value of the color space
     * static const image_color<T> last_value, which states the highest value of the color space
     * static bool is_value(const image_color<T>& value), which returns true if the provided raw value is within the color space
     *
     * If applicable:
     * static void next_value(T &value), which iterates to the next value in the color space. Can be left out if the color space is not iterable.
     *
     * @tparam T Raw value of this color
     */
    template<class ChannelType, int Channels>
    struct pixel_value : public cv::Vec<ChannelType, Channels> {

        using raw_type = cv::Vec<ChannelType, Channels>;
        using channel_type = ChannelType;
        static constexpr int channels = Channels;
        static constexpr int opencv_type = get_opencv_type<ChannelType, Channels>();

        pixel_value() = default;

        explicit pixel_value(cv::Vec<ChannelType, Channels> t_value) : cv::Vec<ChannelType, Channels>(std::move(t_value))  {

        }

        inline operator cv::Vec<ChannelType, Channels>() {
            return *this;
        }

        inline pixel_value<ChannelType, Channels> &operator =(cv::Vec<ChannelType, Channels> t_value) {
            *this = std::move(t_value);
            return *this;
        }

        /**
         * Returns the value as OpenCV scalar
         * @return
         */
        cv::Scalar as_scalar() const {
            return cv::Scalar(*this);
        }

        /**
         * Static cast of this to a cv::Vec.
         * @return
         */
        cv::Vec<ChannelType, Channels> as_vec() const {
            return static_cast<cv::Vec<ChannelType, Channels>>(*this);
        }
    };

    /**
    * Base class for a color. Wraps around a raw color value that is internally stored within the image.
    * To define a color space, the class must inherit from image_color and have following members:
    *
    * static constexpr int opencv_type, which states the internal OpenCV type of the image
    * static constexpr int num_channels, which states the number of channels
    * static const image_color<T> default_value, which states the default value (usually 0/black)
    * static const image_color<T> first_value, which states the lowest value of the color space
    * static const image_color<T> last_value, which states the highest value of the color space
    * static bool is_value(const image_color<T>& value), which returns true if the provided raw value is within the color space
    *
    * If applicable:
    * static void next_value(T &value), which iterates to the next value in the color space. Can be left out if the color space is not iterable.
    *
    * @tparam T Raw value of this color
    */
    template<class ChannelType>
    struct pixel_value<ChannelType, 1> {

        using raw_type = ChannelType;
        using channel_type = ChannelType;
        static constexpr int channels = 1;
        static constexpr int opencv_type = get_opencv_type<ChannelType, 1>();

        pixel_value() = default;

        explicit pixel_value(ChannelType t_value) : value(t_value)  {

        }

        inline operator ChannelType() const {
            return value;
        }

        inline pixel_value<ChannelType, 1> &operator =(ChannelType t_value) {
            value = t_value;
            return *this;
        }

        /**
         * Returns the value as OpenCV scalar
         * @return
         */
        cv::Scalar as_scalar() const {
            return cv::Scalar(value);
        }

        /**
         * Static cast of this to a cv::Vec.
         * @return
         */
        cv::Vec<ChannelType, 1> as_vec() const {
            return cv::Vec<ChannelType, 1>(static_cast<ChannelType>(*this));
        }

        ChannelType value;
    };
}