//
// Created by rgerst on 25.07.18.
//


#pragma once
#include <misaxx/imaging/coixx/toolbox/toolbox.h>
#include <misaxx/imaging/coixx/io/auto_image_io.h>

namespace coixx::toolbox {

    /**
     * Saves the input image using coixx::io::image_io
     * @param t_filename
     * @return
     */
    inline auto save(const io::path &t_filename) {
        return [&t_filename](const auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type ;
            using color_t = typename image_t::color_type;
            io::image_io<color_t>::save(t_img, t_filename);
        };
    }

    /**
     * Loads an image using coixx::io::image_io
     * @tparam Image
     * @tparam C
     * @param t_filename
     * @return
     */
    template<class Image, class C = typename Image::color_type> inline Image load(const io::path &t_filename) {
        return io::image_io<C>::load(t_filename);
    }

    /**
     * Loads an image using coixx::io::auto_image_io and converts it to the target type if required.
     * @tparam Image
     * @tparam C
     * @param t_filename
     * @return
     */
    template<class Image, class C = typename Image::color_type> inline Image auto_load(const io::path &t_filename) {
        return io::auto_image_io<C>::load(t_filename);
    }

}
