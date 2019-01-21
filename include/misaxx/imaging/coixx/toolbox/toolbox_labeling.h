//
// Created by rgerst on 22.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/image.h>
#include <misaxx/core/utils/ref.h>
#include <misaxx/imaging/coixx/converters/semantic_convert.h>

namespace coixx::toolbox::labeling {

    enum class connectivity : int {
        connect_4 = 4,
        connect_8 = 8
    };

    /**
    * Converts the input image to the target type
    * @return
    */
    template<class C = colors::grayscale32s> inline image<C> connected_components(const images::mask &t_mask,
                                                                                         misaxx::utils::ref<typename C::raw_type> t_component_count = misaxx::utils::no_ref,
                                                                                         connectivity t_connectivity = connectivity::connect_4) {

        static_assert(std::is_same<C, colors::labels16u >::value || std::is_same<C, colors::labels32s >::value, "Unsupported label type!");

        image<C> output = image<C>::allocate(t_mask.get_size());

        int count = cv::connectedComponents(t_mask.get_image(),
                                            output.get_image(),
                                            static_cast<int>(t_connectivity),
                                            C::opencv_type);

        misaxx::utils::try_assign_ref(t_component_count, static_cast<typename C::raw_type>(count));

        return output;
    }

    /**
    * Converts the input image to the target type
    * @return
    */
    template<class C = colors::grayscale32s> inline image<C> connected_components(images::mask &&t_mask,
                                                                                        misaxx::utils::ref<typename C::raw_type> t_component_count = misaxx::utils::no_ref,
                                                                                        connectivity t_connectivity = connectivity::connect_4) {
        images::mask v = std::move(t_mask);
        return connected_components<C>(v, t_component_count, t_connectivity);
    }

    /**
     * Assigns an unique label to each non-zero pixel in the mask
     * @tparam C
     * @param t_mask
     * @param t_component_count
     * @return
     */
    template<class C> inline image<C> per_pixel_simple(const images::mask &t_mask, misaxx::utils::ref<typename C::raw_type> t_component_count = misaxx::utils::no_ref) {

        image<C> output(t_mask.get_size(), C::black());

        int label = 0;
        for(int y = 0; y < t_mask.get_height(); ++y) {
            const auto *row_mask = t_mask.row_ptr(y);
            auto *row_label = output.row_ptr(y);

            for(int x = 0; x < t_mask.get_width(); ++x) {
                if(row_mask[x].is_foreground()) {
                    ++label;
                    row_label[x] = static_cast<typename C::raw_type>(label);
                }
            }
        }

        if(t_component_count.has_value()) {
            t_component_count.value().get() = static_cast<typename C::raw_type>(label + 1);
        }

        return output;

    }

    /**
   * Given an image containing the circle centers and where the value represents the circle radius,
   * create a label for each of the circles.
   * Circles with radius 0 are set to the background label (value 0)
   * @tparam Csrc
   * @tparam C
   * @param t_circles
   * @return
   */
    template<class C, class Csrc> inline image<C> circles(const image<Csrc> &t_circles, std::optional<std::reference_wrapper<typename C::raw_type>> t_component_count = std::nullopt) {
        image<C> output(t_circles.get_size(), C::black());

        int label = 0;
        for(int y = 0; y < t_circles.get_height(); ++y) {

            const auto *row_radius = t_circles.row_ptr(y);
            auto *row_label = output.row_ptr(y);

            for(int x = 0; x < t_circles.get_width(); ++x) {
                if(row_radius[x] == 1) {
                    ++label;
                    row_label[x] = static_cast<typename C::raw_type>(label);
                }
                else if(row_radius[x] > 1) {
                    ++label;
                    const auto radius = static_cast<int>(row_radius[x]);
                    cv::circle(output.get_image(), cv::Point(x, y), radius, static_cast<typename C::raw_type>(label), -1);
                }
            }
        }

        if(t_component_count.has_value()) {
            t_component_count.value().get() = static_cast<typename C::raw_type>(label + 1);
        }

        return output;
    }

    /**
     * Given an image containing the circle centers and where the value represents the circle radius,
     * draw the circles onto a mask. Labeling is produced by connected components
     * Circles with radius 0 are ignored.
     * @tparam Csrc
     * @tparam C
     * @param t_circles
     * @return
     */
    template<class C, class Csrc> inline image<C> circles_joined(const image<Csrc> &t_circles, misaxx::utils::ref<typename C::raw_type> t_component_count = misaxx::utils::no_ref) {
        images::mask mask(t_circles.get_size(), colors::mask::background());

        for(int y = 0; y < t_circles.get_height(); ++y) {
            const auto *row_radius = t_circles.row_ptr(y);
            auto *row_mask = mask.row_ptr(y);

            for(int x = 0; x < t_circles.get_width(); ++x) {
                const auto radius = static_cast<int>(row_radius[x]);
                if(radius == 1) {
                    row_mask[x] = colors::mask::foreground();
                }
                else if(radius > 1) {
                    cv::circle(mask.get_image(), cv::Point(x, y), radius, 255, -1);
                }
            }
        }

        return connected_components<C>(mask, t_component_count);
    }

    /**
     * Applies seeded watershed algorithm.
     * The parameters are different to the other labeling algorithms, as seeded_watershed requires initial labels.
     * @tparam C
     * @tparam R
     * @param t_reference
     * @param t_markers
     */
    template<class C> inline void seeded_watershed(const image<C> &t_reference, images::grayscale32s &t_markers) {
        if constexpr (std::is_same<typename C::raw_type, colors::bgr8u>::value) {
            cv::watershed(t_reference.get_image(), t_markers.get_image());
        }
        else {
            images::bgr8u reference = converters::semantic_convert<images::bgr8u>(t_reference);
            cv::watershed(reference.get_image(), t_markers.get_image());
        }
    }
}
