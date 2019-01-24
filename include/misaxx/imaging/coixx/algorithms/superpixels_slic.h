//
// Created by rgerst on 25.07.18.
//


#pragma once

#include <opencv2/ximgproc.hpp>
#include <misaxx/imaging/coixx/image.h>
#include <misaxx/imaging/coixx/algorithms/superpixels_slic_algorithm.h>

namespace coixx {
    /**
    * Wrapper around OpenCV's SLIC algorithm
    */
    struct superpixels_slic {

        superpixels_slic() = default;

        template<class C>
        explicit superpixels_slic(const image<C> &t_img, superpixels_slic_algorithm t_algorithm, int t_region_size,
                                  float t_compactness) : superpixels_slic(t_img.get_mat(), t_algorithm, t_region_size, t_compactness) {

        }

        explicit superpixels_slic(const cv::Mat &t_img, superpixels_slic_algorithm t_algorithm, int t_region_size,
                                  float t_compactness);

        /**
         * Gets the OpenCV instance
         * @return
         */
        cv::ximgproc::SuperpixelSLIC &get_instance();

        /**
         * Gets the OpenCV instance
         * @return
         */
        const cv::ximgproc::SuperpixelSLIC &get_instance() const;

        /**
         * Generates a mask based on the borders of the superpixels
         * @param t_thick_line
         * @return
         */
        images::mask to_mask(bool t_thick_line = false) const;

        /**
         * Extracts the superpixel object labels
         * @return
         */
        images::grayscale32s get_labels() const;

        /**
         * Merges components smaller than a provided size
         * @param t_min_element_size
         */
        void merge_small_components(int t_min_element_size = 25) const;

        /**
         * Returns the number of superpixels
         * @return
         */
        int get_num_superpixels() const;

        /**
         * Iterates the superpixel algorithm
         * @param t_num_iterations
         */
        void iterate(int t_num_iterations) const;

    private:

        cv::Size m_size;
        superpixels_slic_algorithm m_algorithm;
        int m_region_size;
        float m_compactness;
        cv::Ptr<cv::ximgproc::SuperpixelSLIC> m_instance;

    };


}