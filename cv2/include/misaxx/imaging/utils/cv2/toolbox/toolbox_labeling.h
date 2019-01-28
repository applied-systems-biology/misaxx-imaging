//
// Created by rgerst on 28.01.19.
//

#pragma once


#include <misaxx/imaging/utils/cv2/static_types.h>
#include <misaxx/imaging/utils/cv2/connectivity.h>
#include <misaxx/imaging/utils/cv2/recoloring_map.h>
#include <misaxx/imaging/utils/cv2/toolbox/toolbox_recoloring.h>
#include <misaxx/imaging/utils/cv2/label_properties.h>
#include <misaxx/imaging/utils/cv2/labeled_image_properties.h>


namespace cv::toolbox::labeling {

    images::labels connected_components(const images::mask &img, connectivity connectivity);

    /**
     * Removes all labels where the function returns false
     * @tparam Func Function that takes a cv::label_properties<Rows...>::row
     * @param labels
     * @param func
     */
    template<class ...Rows> inline void filter(images::labels &labels, const std::function<bool(const typename cv::label_properties<Rows...>::row&)> &func) {
        cv::identity_recoloring_hashmap<int> recoloring;
        cv::label_properties<Rows...> properties { labels };
        for(const auto &kv : properties.rows) {
            if(!func(kv.second)) {
                recoloring.set_recolor(kv.first, 0);
            }
        }
        toolbox::recolor(labels, recoloring);
    }

    /**
     * Removes all labels where the function returns false
     * @tparam T
     * @tparam Rows
     * @param labels
     * @param reference
     * @param func
     */
    template<typename T, class... Rows> inline void filter(images::labels &labels, const cv::Mat &reference,
            const std::function<bool(const typename cv::labeled_image_properties<T, Rows...>::row&)> &func) {
        cv::identity_recoloring_hashmap<int> recoloring;
        cv::labeled_image_properties<T, Rows...> properties { labels, reference };
        for(const auto &kv : properties.rows) {
            if(!func(kv.second)) {
                recoloring.set_recolor(kv.first, 0);
            }
        }
        toolbox::recolor(labels, recoloring);
    }

}



