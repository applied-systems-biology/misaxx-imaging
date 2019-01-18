//
// Created by rgerst on 23.07.18.
//


#pragma once

#include <misaxx-imaging/utils/percentiles.h>
#include <misaxx-imaging/coixx/histogram.h>
#include <misaxx-imaging/coixx/toolbox/toolbox.h>
#include <misaxx-imaging/coixx/toolbox/toolbox_edge.h>
#include <misaxx-imaging/coixx/toolbox/toolbox_values.h>

namespace coixx::toolbox::statistics {

    /**
   * Counts the pixels of a specified color
   * @return
   */
    template<class C>
    inline int count_color(const image<C> &t_img, const C &t_color) {
        int count = 0;

        for(int y = 0; y < t_img.get_height(); ++y) {
            const auto *row = t_img.row_ptr(y);

            for(int x = 0; x < t_img.get_width(); ++x) {
                if(row[x] == t_color) {
                    ++count;
                }
            }
        }

        return count;
    }

    /**
   * Counts non-zero pixels
   * @return
   */
    template<class C>
    inline int count_non_zero(const image<C> &t_img) {
        return cv::countNonZero(t_img.get_image());
    }

    /**
     * Returns true if the whole image is zero (black)
     * @return
     */
    template<class C>
    inline bool is_black(const image<C> &t_img) {
        return count_non_zero(t_img) == 0;
    }

    /**
     * Returns the minimum pixel value of this image
     * @return
     */
    template<class C, typename RawColor = typename C::raw_type>
    inline RawColor min(const image<C> &t_img) {

        const images::raw &raw_image = t_img.get_image();

        double v;
        cv::minMaxLoc(raw_image, &v);
        return static_cast<RawColor>(v);
    }

    /**
     * Returns the maximum pixel value of this image
     * @return
     */
    template<class C, typename RawColor = typename C::raw_type>
    inline RawColor max(const image<C> &t_img) {

        const images::raw &raw_image = t_img.get_image();

        double v;
        cv::minMaxLoc(raw_image, nullptr, &v);
        return static_cast<RawColor>(v);
    }

    /**
     * Returns the minimum and maximum pixel values of this image in one iteration
     * @param min
     * @param max
     */
    template<class C>
    inline void min_max(const image<C> &t_img, C &min, C &max) {

        const images::raw &raw_image = t_img.get_image();

        double dmin, dmax;
        cv::minMaxLoc(raw_image, &dmin, &dmax);

        min = static_cast<C>(dmin);
        max = static_cast<C>(dmax);
    }

    /**
     * Returns minimum and maximum pixel values within mask
     * @tparam C
     * @tparam RawColor
     * @param t_img
     * @param min
     * @param max
     * @param t_mask
     */
    template<class C>
    inline void min_max_where(const image<C> &t_img, C &min, C &max, const images::mask &t_mask) {
        double dmin = std::numeric_limits<double>::max();
        double dmax = std::numeric_limits<double>::min();

        for(int y = 0; y < t_img.get_height(); ++y) {
            const auto *row_img = t_img.row_ptr(y);
            const auto *row_mask = t_mask.row_ptr(y);

            for (int x = 0; x < t_img.get_width(); ++x) {
                if (row_mask[x].is_foreground()) {
                    dmin = std::min<double>(row_img[x], dmin);
                    dmax = std::max<double>(row_img[x], dmax);
                }
            }
        }

        min = static_cast<C>(dmin);
        max = static_cast<C>(dmax);
    }

    /**
     * Sums the values of the image
     * @tparam C
     * @param t_img
     * @return
     */
    template<class C> inline double get_sum(const image<C> &t_img) {
        double result = 0;
        for(int y = 0; y < t_img.get_height(); ++y) {
            const auto *row = t_img.row_ptr(y);
            for(int x = 0; x < t_img.get_width(); ++x) {
                result += row[x];
            }
        }
        return result;
    }

    /**
     * Sums the values of the image
     * @tparam C
     * @param t_img
     * @param t_mask
     * @return
     */
    template<class C>
    inline double get_sum_where(const image<C> &t_img, const images::mask &t_mask) {
        double result = 0;
        for(int y = 0; y < t_img.get_height(); ++y) {

            const auto *row = t_img.row_ptr(y);
            const auto *row_mask = t_mask.row_ptr(y);

            for(int x = 0; x < t_img.get_width(); ++x) {
                if(row_mask[x].is_foreground()) {
                    result += row[x];
                }
            }
        }
        return result;
    }

    /**
     * Calculates the number of border pixels in the mask
     * @tparam C
     * @param t_img
     * @return
     */
    inline int perimeter_laplacian(const images::mask &t_img) {
        auto copy = t_img.clone() << edge::laplacian();
        return count_non_zero(copy);
    }

    /**
     * Returns true if this image has only 1 color
     * @tparam C
     * @param t_image
     * @return
     */
    template<class C> inline bool is_monochrome(const image<C> &t_image) {
        typename C::raw_type m1, m2;
        min_max(t_image, m1, m2);
        return m1 == m2;
    }

    /**
    * Gets the mean color value
    * @return
    */
    template<class C>
    inline double get_mean(const image<C> &t_img) {
        return static_cast<double>(cv::mean(t_img.get_image())[0]);
    }

    /**
     * Gets the mean color value
     * @return
     */
    template<class C>
    inline double get_mean_where(const image<C> &t_img, const images::mask &t_mask) {
        return static_cast<double>(cv::mean(t_img.get_image(), t_mask.get_image())[0]);
    }

    /**
    * Returns the minimum and maximum pixel values of this image in one iteration.
    * Updates the minimum and maximum values
    * @param min
    * @param max
    */
    template<class C>
    inline void update_min_max(const image<C> &t_img, C &min, C &max) {

        const images::raw &raw_image = t_img.get_image();

        double dmin, dmax;
        cv::minMaxLoc(raw_image, &dmin, &dmax);

        min = std::min(static_cast<C>(dmin), min);
        max = std::max(static_cast<C>(dmax), max);
    }

    /**
     * Returns the minimum and maximum pixel values of this image in one iteration.
     * This function returns doubles (highest scalar type supported by OpenCV)
     * @param min
     * @param max
     */
    template<class C>
    inline void min_max_(const image<C> &t_img, double &min, double &max) {

        const images::raw &raw_image = t_img.get_image();
        cv::minMaxLoc(raw_image, &min, &max);
    }

    /**
     * Updates an existing histogram
     * @tparam Histogram
     * @tparam C
     * @param t_img
     * @param histogram
     * @return
     */
    template<class C> void update_histogram(const image<C>&t_img, mutable_histogram<C> &histogram) {
        for(int y = 0; y < t_img.get_height(); ++y) {
            const auto *row_img = t_img.row_ptr(y);
            for(int x = 0; x < t_img.get_width(); ++x) {
                histogram.count(row_img[x]);
            }
        }
    }

    /**
    * Updates an existing histogram
    * @tparam Histogram
    * @tparam C
    * @param t_img
    * @param histogram
    * @return
    */
    template<class C> void update_histogram_where(const image<C>&t_img, mutable_histogram<C> &histogram, const images::mask &t_mask) {
        for(int y = 0; y < t_img.get_height(); ++y) {
            const auto *row_img = t_img.row_ptr(y);
            const auto *row_mask = t_mask.row_ptr(y);
            for(int x = 0; x < t_img.get_width(); ++x) {
                if(row_mask[x].is_foreground()) {
                    histogram.count(row_img[x]);
                }
            }
        }
    }

    /**
     * Calculates a histogram of given image.
     * The histogram maps from the raw color value to int
     * @tparam C
     * @tparam RawColor
     * @param t_img
     * @return
     */
    template<class C> hashmap_histogram<C> get_histogram(const image<C> &t_img) {

        hashmap_histogram<C> histogram;
        update_histogram(t_img, histogram);
        return histogram;
    }

    /**
     * Calculates a histogram of given image.
     * The histogram maps from the raw color value to int
     * @tparam C
     * @tparam RawColor
     * @param t_img
     * @return
     */
    template<class C> hashmap_histogram<C> get_histogram_where(const image<C> &t_img, const images::mask &t_mask) {

        hashmap_histogram<C> histogram;
        update_histogram_where(t_img, histogram, t_mask);
        return histogram;
    }

    /**
     * Finds the percentiles of an image as the specified type
     * @tparam C
     * @tparam U
     * @param t_img
     * @param t_percentiles
     * @param t_result
     * @return
     */
    template<class C>
    inline void get_percentiles(const image<C> &t_img,
                                const std::vector<double> &t_percentiles,
                                std::vector<C> &t_result) {

        // TODO: Implement histogram based percentile calculation (faster)
        //        if constexpr(std::is_integral<raw_color_type>::value) {
//            const auto hist = get_histogram<MapTypeTag>(t_img);
//            misaxx::utils::math::percentiles::find_percentiles_fast<raw_color_type, raw_color_type>(t_result, hist, t_percentiles);
//        } else {
            std::vector<C> pixels;
            t_img << values::get(std::back_inserter(pixels));
            misaxx_imaging::utils::find_percentiles<C, C>(t_result, pixels, t_percentiles, true);
//        }

    }


    /**
     * Gets percentiles of values inside the mask
     * This function will return the percentiles as doubles (highest scalar type supported by OpenCV)
     * @param t_mask
     * @param t_percentiles
     * @param t_result
     */
    template<class C>
    inline void get_percentiles_where(const image<C> &t_img,
                                      const images::mask &t_mask,
                                      const std::vector<double> &t_percentiles,
                                      std::vector<typename C::raw_type> &t_result) {

        // TODO: Implement histogram based percentile calculation (faster)
//        if constexpr(std::is_integral<raw_color_type>::value) {
//            const auto hist = get_histogram_where<MapTypeTag>(t_img, t_mask);
//            misaxx::utils::math::percentiles::find_percentiles_fast<raw_color_type, raw_color_type>(t_result, hist, t_percentiles);
//        } else {
            std::vector<C> pixels;
            t_img << values::get_where(std::back_inserter(pixels), t_mask);
            misaxx_imaging::utils::find_percentiles<C, C>(t_result, pixels, t_percentiles, true);
//        }

    }

    /**
     * Returns one percentile
     * @tparam C
     * @param t_img
     * @param t_percentile
     * @return
     */
    template<class C>
    inline C get_percentile(const image<C> &t_img,
                                                         double t_percentile) {
        std::vector<C> result;
        get_percentiles(t_img, {t_percentile}, result);
        return result[0];
    }

    /**
     * Returns one percentile
     * @tparam C
     * @param t_img
     * @param t_percentile
     * @param t_mask
     * @return
     */
    template<class C>
    inline C get_percentile_where(const image<C> &t_img,
                                                               double t_percentile,
                                                               const images::mask &t_mask) {
        std::vector<C> result;
        get_percentiles_where(t_img, t_mask, {t_percentile}, result);
        return result[0];
    }

    /**
     * Returns one percentile
     * @tparam C
     * @param t_img
     * @param t_percentile
     * @return
     */
    template<typename U, class C>
    inline U get_percentile_as(const image<C> &t_img,
                               double t_percentile) {
        return static_cast<U>(get_percentile(t_img, t_percentile));
    }

    /**
     * Returns one percentile
     * @tparam C
     * @param t_img
     * @param t_percentile
     * @param t_mask
     * @return
     */
    template<typename U, class C>
    inline U get_percentile_where_as(const image<C> &t_img,
                                     double t_percentile,
                                     const images::mask &t_mask) {
        return static_cast<U>(get_percentile_where(t_img, t_percentile, t_mask));
    }
}
