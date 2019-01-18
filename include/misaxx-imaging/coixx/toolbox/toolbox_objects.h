//
// Created by rgerst on 25.06.18.
//


#pragma once

#include <misaxx-imaging/coixx/image.h>
#include <misaxx/utils/math/misc.h>
#include <misaxx-imaging/coixx/toolbox/toolbox.h>
#include <misaxx-imaging/coixx/toolbox/toolbox_morph_cross.h>
#include <misaxx-imaging/coixx/toolbox/toolbox_recoloring.h>
#include <misaxx-imaging/coixx/objects/label_properties.h>
#include <misaxx-imaging/coixx/objects/label_pixel_count.h>
#include <misaxx-imaging/coixx/objects/object_properties.h>
#include <misaxx-imaging/coixx/objects/object_pixel_stats.h>
#include <misaxx-imaging/coixx/objects/object_average_intensity.h>

namespace coixx::toolbox::objects {

    template<class ... PropertyTags> using label_properties = label_properties<colors::labels, PropertyTags...>;
    template<class ReferenceImage, class ... PropertyTags> using object_properties = object_properties<typename ReferenceImage::color_type, colors::labels, PropertyTags...>;

    /**
     * Filters the objects in a labeled image by the properties of each label in the reference image.
     * Filtered-out object will be recolored to 0 (black)
     * @tparam C
     * @tparam Func Takes an labeled_image_properties<C>::properties reference and returns true if the object should be kept
     * @param t_reference
     * @param t_decider
     * @return
     */
    template<class Properties, class C, class Recoloring = identity_recoloring_hashmap<colors::labels>, class Func>
    inline auto filter_objects(const image<C> &t_reference, const Func &t_decider) {
        return [&](images::grayscale32s &t_img) {
            Properties properties(t_reference, t_img);
            Recoloring lut;

            for (const auto &kv : properties) {
                if (!t_decider(kv.second)) {
                    lut.set_recolor(kv.first, colors::labels::background());
                }
            }

            t_img << recoloring::recolor(lut);
        };
    }

    /**
     * Filters the objects in a labeled image.
     * @tparam C
     * @tparam Func Takes an label_properties<C>::properties reference and returns true if the object should be kept
     * @param t_reference
     * @param t_decider
     * @return
     */
    template<class Properties, class Recoloring = identity_recoloring_hashmap<colors::labels>, class Func>
    inline auto filter_labels(const Func &t_decider) {
        return [&](images::grayscale32s &t_img) {
            Properties properties(t_img);
            Recoloring lut;

            for (const auto &kv : properties) {
                if (!t_decider(kv.second)) {
                    lut.set_recolor(kv.first, colors::labels::background());
                }
            }

            t_img << recoloring::recolor(lut);
        };
    }

    /**
     * Filters objects with low average intensity.
     * @tparam C
     * @param t_reference
     * @param t_min_average_intensity
     * @return
     */
    template<class C>
    inline auto filter_low_average_intensity_objects(const image<C> &t_reference, const double t_min_average_intensity) {
        return filter_objects<object_properties<image<C>, object_average_intensity> >(t_reference, [t_min_average_intensity](const auto &prop) {
            auto avg_intensity = prop.template get<object_average_intensity>().average_intensity();
            return avg_intensity >= t_min_average_intensity;
        });
    }

    /**
     * Filters objects with low size in number of pixels
     * @param t_min_pixels
     * @return
     */
    inline auto filter_small_labels(const int t_min_pixels) {
        return filter_labels<label_properties<label_pixel_count>>([t_min_pixels](const auto &prop) {
            return prop.template get<label_pixel_count>().pixels >= t_min_pixels;
        });
    }

    /**
     * Sets all non-border pixels of the label image to background (0).
     * @return
     */
    inline auto to_border_only() {
        return morph::sustaining_gradient_cross();
    }

    /**
     * Further splits the labels of the input image by the labels of the other image.
     * By default zero-labels are seen as background and ignored.
     *
     * Internally uses the cantor-pairing to calculate the new label.
     * @param t_other
     * @param t_ignore_src_zero If true, no new labels are created if the target image is zero at a pixel
     * @param t_ignore_other_zero If true, no new labels are created if the other image is zero at a pixel
     * @return
     */
    inline auto diversify_with(const images::grayscale32s &t_other, bool t_ignore_src_zero = true) {
        return [&t_other, t_ignore_src_zero](images::grayscale32s &t_img) {
            assert_same_size(t_img, t_other);

            for (int y = 0; y < t_img.get_height(); ++y) {

                colors::labels *row = t_img.row_ptr(y);
                const colors::labels *row_other = t_other.row_ptr(y);

                for (int x = 0; x < t_img.get_width(); ++x) {
                    if (t_ignore_src_zero && row[x].is_background())
                        continue;
                    row[x] = misaxx::utils::math::cantor_pairing(row[x], row_other[x]);
                }
            }
        };
    }

}
