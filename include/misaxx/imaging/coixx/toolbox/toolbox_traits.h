//
// Created by rgerst on 26.07.18.
//


#pragma once

#include <type_traits>
#include <stdexcept>

/**
 * Contains query functions that provide
 */
namespace coixx::toolbox::traits {

    /**
     * Extracts the underlying image type from a decltype(img) inside a filter function
     *
     * \code{.cpp}
     * auto my_filter() {
     *  return [](auto &img) {
     *      traits::image_type<decltype(img)> &image = img;
     *      traits::color_type<decltype(img)> color(0);
     *      image.at(0,0) = color;
     *  }
     * }
     * \endcode
     */
    template<class DeclType> using image_type = typename std::remove_reference<DeclType>::type;

    /**
     * Extracts the underlying color type from a decltype(img) inside a filter function
     *
     * \code{.cpp}
     * auto my_filter() {
     *  return [](auto &img) {
     *      traits::image_type<decltype(img)> &image = img;
     *      traits::color_type<decltype(img)> color(0);
     *      image.at(0,0) = color;
     *  }
     * }
     * \endcode
     */
    template<class DeclType> using color_type = typename image_type<DeclType>::color_type;

    /**
     * Returns true if the provided image is a grayscale image
     * @tparam Image
     * @param t_img
     * @return
     */
    template<class Image>
    inline constexpr bool is_grayscale(const Image &) {
        return Image::color_type::channels == 1;
    }

    /**
     * Returns true if ImageOrColor is compatible to Image, namely
     * if ImageOrColor is the same type as Image or Image::color_type
     * @tparam ImageOrColor Image or color type
     * @tparam Image
     * @param t_img
     * @return
     */
    template<class ImageOrColor, class Image> inline constexpr bool is_compatible(const Image &) {
        return std::is_same<ImageOrColor, Image>::value || std::is_same<ImageOrColor, typename Image::color_type>::value;
    }

    /**
    * Returns true if the provided image is a grayscale image with integral data
    * @tparam Image
    * @param t_img
    * @return
    */
    template<class Image>
    inline constexpr bool is_integral_grayscale_image(const Image &) {
        return std::is_integral<typename Image::color_type::channel_type>::value;
    }

    /**
    * Returns true if the provided image is a grayscale image with floating point data
    * @tparam Image
    * @param t_img
    * @return
    */
    template<class Image>
    inline constexpr bool is_floating_grayscale_image(const Image &) {
        return std::is_floating_point<typename Image::color_type::channel_type>::value;
    }

    /**
    * Returns true if the provided image is a grayscale image with floating point data
    * @tparam Image
    * @param t_img
    * @return
    */
    template<class OtherImage, class Image>
    inline constexpr bool is_same(const Image &) {
        return std::is_same<Image, OtherImage>::value;
    }
}