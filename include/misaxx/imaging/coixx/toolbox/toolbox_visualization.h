//
// Created by rgerst on 27.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/objects/label_centroid_position.h>
#include <unordered_set>
#include <misaxx/imaging/coixx/image.h>
#include <misaxx/imaging/coixx/structuring_element.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_morph.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_edge.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_text.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_recoloring.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_mask.h>
#include <misaxx/imaging/coixx/converters/semantic_convert.h>
#include <misaxx/imaging/coixx/objects/label_properties.h>
#include <misaxx/imaging/coixx/objects/object_properties.h>

namespace coixx::toolbox::visualization {

    /**
    * List of different modes supported by this filter
    */
    enum mask_visualization {
        /**
         * Replaces the original image with the outline color
         */
                replace,
        /**
         * Creates a border around the mask
         */
                border
    };

    /**
     * Visualizes one mask to the target image
     * @param t_target
     * @param t_mask
     * @param t_color
     * @param t_mode
     * @param t_border_thickness
     */
    inline void mask_(images::bgr8u &t_target,
                      const images::mask& t_mask,
                      const colors::bgr8u& t_color,
                      mask_visualization t_mode = mask_visualization::border,
                      int t_border_thickness = 1) {

        if(t_target.get_size() != t_mask.get_size()) {
            throw std::runtime_error("Image and mask must have the same size!");
        }

        images::grayscale8u mask = t_mask.clone();

        // If we only want a border, use an edge detector to find the outline
        switch(t_mode) {
            case mask_visualization::border:
            {
                mask << morph::gradient(structuring_element::ellipse(t_border_thickness * 2 + 1));
                t_target << values::set_where(t_color, mask);
            }
                break;
            case mask_visualization::replace:
            {
                // We color the image according to the segmented region
                t_target << values::set_where(t_color, mask);
            }
                break;
            default:
                throw std::runtime_error("Unsupported mode");
        }
    }

    /**
     * Visualizes a set of masks
     * @tparam C
     * @tparam R
     * @param t_masks
     * @param t_img
     * @param t_colors
     * @param t_mode
     * @param t_border_thickness
     * @return
     */
    template<class C> inline images::bgr8u masks(const std::vector<std::reference_wrapper<const images::mask>> &t_masks,
                                                 const image<C> & t_img,
                                                 const std::vector<colors::bgr8u> &t_colors,
                                                 mask_visualization t_mode = mask_visualization::border,
                                                 int t_border_thickness = 1) {
        if(t_masks.size() != t_colors.size()) {
            throw std::runtime_error("Each mask requires a color!");
        }
        images::bgr8u output = converters::semantic_convert<images::bgr8u>(t_img);

        for(size_t i = 0; i < t_masks.size(); ++i) {
            mask_(output, t_masks[i].get(), t_colors[i], t_mode, t_border_thickness);
        }

        return output;
    }

    /**
     * Visualizes a set of masks. The colors are generated from HSV color space.
     * @tparam C
     * @tparam R
     * @param t_masks
     * @param t_img
     * @param t_mode
     * @param t_border_thickness
     * @return
     */
    template<class C> inline images::bgr8u masks(const std::vector<std::reference_wrapper<const images::mask>> &t_masks,
                                                 const image<C> & t_img,
                                                 mask_visualization t_mode = mask_visualization::border,
                                                 int t_border_thickness = 1) {
        std::vector<colors::bgr8u> colors;
        colors.reserve(t_masks.size());

        for(size_t i = 0; i < t_masks.size(); ++i) {
            colors::hsv8u col = colors::hsv8u::from_double(i * (1.0 / t_masks.size()), 1, 1);
            colors.emplace_back(converters::semantic_convert<colors::bgr8u>(col));
        }

        return masks(t_masks, t_img, colors, t_mode, t_border_thickness);
    }

    /**
     * Visualizes one mask. The default color is red (#FF0000)
     * @tparam C
     * @tparam R
     * @param t_masks
     * @param t_img
     * @param t_mode
     * @param t_border_thickness
     * @return
     */
    template<class C>
    inline images::bgr8u mask(const images::mask &t_mask,
                              const image<C> &t_img,
                              mask_visualization t_mode = mask_visualization::border,
                              const colors::bgr8u &t_color = colors::bgr8u("#FF0000"),
                              int t_border_thickness = 1) {
        return masks({t_mask}, t_img, {t_color}, t_mode, t_border_thickness);
    }

    /**
     * Creates a colored image that assigns a color to each individual label.
     * Colors are generated from HSV color space.
     * This overload uses a set of known labels as reference insead of a minimum and maximum group.
     * @param t_labels
     * @param t_known_labels
     * @return
     */
    inline images::bgr8u labels(const images::labels &t_labels, const std::unordered_set<colors::labels> &t_known_labels) {

        recoloring_hashmap<colors::labels, colors::bgr8u> lut;

        int label_index = 0;

        for(colors::labels label : t_known_labels) {
            double hue = label_index / (1.0 * t_known_labels.size());

            colors::hsv8u color = colors::hsv8u::from_double(hue, 1, 1);
            lut.set_recolor(label, semantic_convert<colors::bgr8u>(color));
            ++label_index;
        }

        lut.set_recolor(colors::labels::background(), colors::bgr8u::black());

        // Apply the LUT
        images::bgr8u output(t_labels.get_size(), colors::bgr8u::black());
        recoloring::recolor_between(t_labels, output, lut);

        return output.move();
    }

    /**
     * Creates a colored image that assigns a color to each individual label.
     * Colors are generated from HSV color space.
     * @param t_labels
     * @return
     */
    inline images::bgr8u labels(const images::labels &t_labels, colors::labels group_min, colors::labels group_max) {
        int num_groups = group_max - group_min + 1;

        // Build our LUT
        recoloring_hashmap<colors::grayscale32s, colors::bgr8u> lut;

        for(colors::labels group = std::max(colors::labels::background(), group_min); group <= group_max; ++group) {

            double hue = (group - group_min) / (1.0 * num_groups);

            colors::hsv8u color = colors::hsv8u::from_double(hue, 1, 1);

            lut.set_recolor(group, semantic_convert<colors::bgr8u>(color));
        }

        lut.set_recolor(colors::labels::background(), colors::bgr8u::black());

        // Apply the LUT
        images::bgr8u output(t_labels.get_size(), colors::bgr8u::black());
        recoloring::recolor_between(t_labels, output, lut);

        return output.move();
    }

    /**
     * Creates a colored image that assigns a color to each individual label.
     * Colors are generated from HSV color space.
     * @param t_labels
     * @return
     */
    inline images::bgr8u labels(const images::grayscale32s &t_labels) {
        colors::labels group_min, group_max;
        statistics::min_max(t_labels, group_min, group_max);
        return labels(t_labels, group_min, group_max);
    }

    /**
     * Visualizes the borders between labels
     * @tparam C
     * @param t_labels
     * @param t_reference
     * @return
     */
    template<class C> inline images::bgr8u label_borders(const images::grayscale32s &t_labels, const image<C> &t_reference) {
        auto borders = t_labels.clone() << edge::laplacian();
        return mask(mask::from(borders), t_reference);
    }

    /**
     * Given a matrix of circle radii, visualize the circles onto the reference image
     * @tparam C
     * @param t_circle_sizes
     * @return
     */
    template<class Csize, class C> inline images::bgr8u circles(const image<Csize> &t_circle_sizes, const image<C> &t_reference, const colors::bgr8u &t_color = colors::bgr8u("#FF0000")) {
        images::bgr8u output = semantic_convert<images::bgr8u>(t_reference);

        for(int y = 0; y < t_reference.get_height(); ++y) {
            const auto *row_size = t_circle_sizes.row_ptr(y);
            for(int x = 0; x < t_reference.get_width(); ++x) {
                const auto radius = static_cast<int>(row_size[x]);
                if(radius > 0) {
                    cv::circle(output.get_mat(), cv::Point(x, y), radius, t_color.as_scalar());
                }
            }
        }

        return output;
    }

    /**
     * Draws information about each label on top of the label centroid points.
     * @tparam Function Function that oututs a std::string for an input label id (int)
     * @param t_labels
     * @param t_function
     * @return
     */
    template<class Function> inline auto with_label_information(const images::grayscale32s &t_labels, const Function &t_function, const text::typeface &t_typeface = text::typeface(), const colors::bgr8u &t_color = colors::bgr8u::white()) {
        return [&](images::bgr8u &t_img) {
            for(const auto &prop : label_properties<colors::grayscale32s, label_centroid_position> (t_labels)) {
                std::string label_text = t_function(prop.first);
                t_img << text::draw_text_centered(label_text, t_typeface, prop.second.get<label_centroid_position>().get_centroid(), t_color, text::text_centering::vertical_and_horizontal);
            }
        };
    }

    /**
     * Draws the label id of each label on top of the label centroid points.
     * If you want to customize the drawn text, use with_label_information() instead.
     * @param t_labels
     * @param t_typeface
     * @param t_color
     * @return
     */
    inline auto with_label_ids(const images::grayscale32s &t_labels, const text::typeface &t_typeface, const colors::bgr8u &t_color = colors::bgr8u::white()) {
        return with_label_information(t_labels, [](int label) -> std::string { return std::to_string(label); }, t_typeface, t_color);
    }

}
