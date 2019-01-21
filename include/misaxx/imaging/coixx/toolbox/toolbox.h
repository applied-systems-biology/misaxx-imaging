//
// Created by rgerst on 22.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/image.h>
#include <misaxx/imaging/coixx/converters/semantic_convert.h>
#include <misaxx/imaging/coixx/converters/hard_convert.h>
#include <misaxx/imaging/coixx/converters/reinterpret_convert.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_traits.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_assert.h>
//#include "../color_converters.h"

/**
 * Toolbox of filters and accessors that allow manipulation and information extraction from an image.
 * There are two types of toolbox functions:
 * * "normal" functions take the image as parameter and return a specific value from them
 * * "inplace" functions return a function template that does noting except if combined with the << operator.
 *
 * Normal function example:
 * auto img = toolbox::from_row(cv::Mat())
 * auto visualization = toolbox::visualization::labels(label_img);
 *
 * Inplace function example:
 * images::mask img;
 * img << toolbox::binarize::otsu();
 *
 * Inplace-functions can be used to build long chains of filters:
 * images::mask thresholded = conversion::semantic_convert<images::mask>(float_image) << toolbox::binarize::otsu() << toolbox::bitwise::bw_or(other_mask);
 *
 * toolbox::values::backup(), toolbox::save(), toolbox::show() and toolbox::show_and_wait() are inplace functions that allow
 * * extracting images from within the chain
 * * saving images within a chain
 * * displaying images within a chain before continuing with the operations
 *
 */
namespace coixx::toolbox {

    /**
     * Applies filter to an image
     * @tparam C
     * @tparam Function
     * @param sink
     * @param t_filter
     * @return
     */
    template<class C, class Function> inline const image<C>& operator <<(const image<C> &sink, const Function &t_filter) {
        t_filter(sink);
        return sink;
    }

    /**
     * Applies filter to an image
     * @tparam C
     * @tparam Function
     * @param sink
     * @param t_filter
     * @return
     */
    template<class C, class Function> inline image<C>& operator <<(image<C> &sink, const Function &t_filter) {
        t_filter(sink);
        return sink;
    }

    /**
     * Applies filter to an image
     * @tparam C
     * @tparam Function
     * @param sink
     * @param t_filter
     * @return
     */
    template<class C, class Function> inline image<C> operator <<(image<C> &&sink, const Function &t_filter) {
        t_filter(sink);
        return std::forward<image<C>>(sink);
    }

    /**
     * Creates an image from an OpenCV image
     * @tparam Image
     * @param raw
     * @return
     */
    template<class Image> inline Image from_raw(cv::Mat &&raw) {
        return Image(raw);
    }

    /**
     * Creates an image from an OpenCV image
     * @tparam Image
     * @param raw
     * @return
     */
    template<class Image> inline Image from_raw(const cv::Mat &raw) {
        return Image(raw);
    }

    /**
     * Convenience import of conversion operators.
     */
    using namespace coixx::converters;
}

