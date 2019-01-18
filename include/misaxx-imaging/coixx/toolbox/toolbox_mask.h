//
// Created by rgerst on 26.06.18.
//


#pragma once

#include <misaxx-imaging/coixx/image.h>
#include <misaxx-imaging/coixx/toolbox/toolbox_bitwise.h>
#include <misaxx-imaging/coixx/toolbox/toolbox_binarize.h>

namespace coixx::toolbox::mask {

    /**
     * Converts the image to a mask. The resulting mask has a value of 255 if the input value is larger than min_signal, otherwise 0.
     * @tparam Image
     * @tparam Csrc
     * @param sink
     * @return
     */
    template <class Csrc> inline images::mask from(const image<Csrc> &sink, typename Csrc::raw_type min_signal = 0) {
        return images::mask(sink.get_image() > min_signal);
    }

    /**
     * Converts the image to a mask. The resulting mask has a value of 0 if the input value is larger than min_signal, otherwise 255.
     * @tparam Image
     * @tparam Csrc
     * @param sink
     * @return
     */
    template <class Csrc> inline images::mask from_inv(const image<Csrc> &sink, typename Csrc::raw_type min_signal = 0) {
        return images::mask(sink.get_image() <= min_signal);
    }

    /**
     * Binarizes a images::mask image, so all colors > 0 are set to 255, otherwise to 0
     * @return
     */
    inline auto binarize() {
        return binarize::threshold(colors::mask::black());
    }

    /**
     * Merges two masks together. Wrapper around toolbox::bitwise::bw_or()
     * @param t_other
     * @return
     */
    inline auto merge(const images::mask &t_other) {
        return bitwise::OR(t_other);
    }

}
