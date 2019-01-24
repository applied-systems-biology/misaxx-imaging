//
// Created by rgerst on 25.06.18.
//


#pragma once

#include <opencv2/opencv.hpp>
#include <misaxx/imaging/coixx/image.h>

namespace coixx::toolbox::distance_transform {

    enum class distance_type : int{
        dist_l1 = cv::DIST_L1,
        dist_l2 = cv::DIST_L2,
        dist_c = cv::DIST_C
    };

    enum class mask_size : int {
        mask_3 = cv::DIST_MASK_3,
        mask_5 = cv::DIST_MASK_5,
        mask_precise = cv::DIST_MASK_PRECISE
    };

    /**
     * Result type for the full distance transform
     */
    struct distance_transform_result {
        images::grayscale_float distances;
        images::grayscale32s voronoi_labels;
    };

    /**
     * Returns the distance transform of the mask
     * @param t_distance_type
     * @param t_mask_size
     * @return
     */
    inline images::grayscale_float distance_transform(const images::mask &t_img, distance_type t_distance_type = distance_type::dist_l2, mask_size t_mask_size = mask_size::mask_3) {
        images::grayscale_float result(t_img.get_size());
        cv::distanceTransform(t_img.get_mat(), result.get_mat(), static_cast<int>(t_distance_type), static_cast<int>(t_mask_size), result.get_open_cv_type());
        return result;
    }

    /**
     * Applies distance transform and returns the distance of the pixels and the voronoi partitioning
     * @param t_img
     * @param t_distance_type
     * @param t_mask_size
     * @return
     */
    inline distance_transform_result distance_transform_voronoi(const images::mask &t_img, distance_type t_distance_type = distance_type::dist_l2, mask_size t_mask_size = mask_size::mask_3) {
        distance_transform_result result;
        result.distances = images::grayscale_float(t_img.get_size());
        result.voronoi_labels = images::grayscale32s(t_img.get_size());
        cv::distanceTransform(t_img.get_mat(),
                              result.distances.get_mat(),
                              result.voronoi_labels.get_mat(),
                              static_cast<int>(t_distance_type),
                              static_cast<int>(t_mask_size));
        return result;
    }

    /**
     * Convenience wrapper around distance_transform_voronoi() that only returns the voronoi labeling
     * @param t_img
     * @param t_distance_type
     * @param t_mask_size
     * @return
     */
    inline images::grayscale32s voronoi(const images::mask &t_img, distance_type t_distance_type = distance_type::dist_l2, mask_size t_mask_size = mask_size::mask_3) {
        return distance_transform_voronoi(t_img, t_distance_type, t_mask_size).voronoi_labels;
    }
}
