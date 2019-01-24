//
// Created by rgerst on 28.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/structuring_element.h>
#include <misaxx/imaging/coixx/image.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_morph.h>

namespace coixx::toolbox::localminmax {

    /**
     * Responds to all maxima within radius
     * @tparam C
     * @param t_img
     * @param t_radius
     * @return
     */
    template<class C>
    inline images::mask local_max_morph(const image<C> &t_img, int t_radius) {
        auto morphed = t_img.clone() << morph::dilate(structuring_element::circle(t_radius * 2 + 1));
        return images::mask(t_img.get_mat() == morphed.get_mat());
    }

    /**
    * Responds to all minima within given radius.
     * This includes duplicate minima.
    * @tparam C
    * @tparam R
    * @param t_img
    */
    template<class C>
    inline images::mask local_min_morph(const image<C> &t_img, int t_radius) {
        auto morphed = t_img.clone() << morph::erode(structuring_element::circle(t_radius * 2 + 1));
        return images::mask(t_img.get_mat() == morphed.get_mat());
    }

    /**
    * Responds to exclusive maxima within given radius.
    * @tparam C
    * @tparam R
    * @param t_img
    */
    template<class C>
    inline images::mask local_exclusive_max_morph(const image<C> &t_img, int t_radius) {
        auto morphed = t_img.clone() << morph::dilate(structuring_element::circle_with_hole(t_radius * 2 + 1));
        return images::mask(t_img.get_mat() > morphed.get_mat()); // Important!
    }

    /**
    * Responds to exclusive minima within given radius.
    * @tparam C
    * @tparam R
    * @param t_img
    */
    template<class C>
    inline images::mask local_exclusive_min_morph(const image<C> &t_img, int t_radius) {
        auto morphed = t_img.clone() << morph::erode(structuring_element::circle_with_hole(t_radius * 2 + 1));
        return images::mask(t_img.get_mat() < morphed.get_mat()); // Important!
    }

}
