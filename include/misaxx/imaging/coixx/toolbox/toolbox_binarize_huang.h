//
// Created by rgerst on 22.06.18.
//


#pragma once

#include <misaxx/imaging/utils/thresholding.h>
#include <opencv2/core/types.hpp>
#include <misaxx/imaging/coixx/image.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_binarize.h>
#include <misaxx/imaging/coixx/cumulative_histogram.h>

namespace coixx::toolbox::binarize {

    namespace huang {

        /**
        * Shannon function used for Huang thresholding
        *
        * Will return 0 if input is 1 or 0
        * @param mu
        * @return
        */
        inline double shannon_f(const double mu) {
            if(mu == 1 || mu == 0)
                return 0;
            return -mu * std::log(mu) - (1.0 - mu) * std::log(1.0 - mu);
        }

        inline double huang_membership(const histogram<colors::mask>&hist, const double mu_0, const double mu_1, const int g, const int threshold) {

            const uchar hist_min = hist.get_min_key();
            const uchar hist_max = hist.get_max_key();

            const double membership_constant = hist_max - hist_min;
            double mu_x;

            if(g <= threshold) {
                mu_x = 1.0 / (1.0 + std::abs(g - mu_0) / membership_constant);
            }
            else {
                mu_x = 1.0 / (1.0 + std::abs(g - mu_1) / membership_constant);
            }

            return mu_x;
        }

        /**
     * Used as fuzzyness measurement
     * @param histogram
     * @param threshold
     * @param mu_0
     * @param mu_1
     * @param t_img_size
     * @return
     */
        inline double huang_shannon_fuzzyness(const histogram<colors::mask>&hist, const int threshold, const double mu_0, const double mu_1, const cv::Size t_img_size) {

            const uchar hist_min = hist.get_min_key();
            const uchar hist_max = hist.get_max_key();
            double energy = 0;

            for(int g = hist_min; g <= hist_max; ++g) {
                const double mu_x = huang_membership(hist, mu_0, mu_1, g, threshold);
                energy += shannon_f(mu_x) * hist.get_count(colors::mask(g));
            }

            energy /= t_img_size.width * t_img_size.height * M_LN2;
            return energy;
        }

        /**
         * Used as fuzzyness measurement
         * @param histogram
         * @param threshold
         * @param mu_0
         * @param mu_1
         * @param t_img_size
         * @param p
         * @return
         */
        inline double huang_yager_fuzzyness(const histogram<colors::mask>&hist, const int threshold, const double mu_0, const double mu_1, const cv::Size t_img_size, const double p = 2) {

            const uchar hist_min = hist.get_min_key();
            const uchar hist_max = hist.get_max_key();

            double distance = 0;
            for(int g = hist_min; g <= hist_max; ++g) {
                const double mu_x = huang_membership(hist, mu_0, mu_1, g, threshold);
                distance += std::pow(std::abs(mu_x - (1.0 - mu_x)), p);
            }
            distance = std::pow(distance, 1.0 / p) * hist.get_count(colors::mask(threshold));

            return 1.0 - (distance / std::pow(t_img_size.width * t_img_size.height, 1.0 / p));
        }

    }

    /**
     * Applies automatic thresholding proposed by Huang et. al.
     * This implementation uses the measurement of fuzzyness based on the Shannon function.
     *
     * Ported directly from the paper.
     *
     * Liang-Kai Huang and Mao-Jiun J. Wang,
     * “Image Thresholding by Minimizing the Measures of Fuzziness,”
     * Pattern Recognition 28, no. 1 (January 1, 1995): 41–51,
     * https://doi.org/10.1016/0031-3203(94)E0043-K.
     *
     * @param t_threshold
     * @return
     */
    inline auto huang_shannon() {
        return [](images::mask &t_img) {

            using namespace huang;

            /**
             * Build the necessary histograms for the calculations
             */
            auto hist = statistics::get_histogram(t_img);
            const uchar hist_min = hist.get_min_key();
            const uchar hist_max = hist.get_max_key();

            if(hist_min == hist_max) {
                t_img << values::set(colors::mask::foreground());
                return;
            }

            auto cumulative_histogram = wrapping_cumulative_histogram<colors::mask>(hist);
            auto weighted_histogram = wrapping_weighted_cumulative_histogram<colors::mask>(hist);

            const auto max_value = hist_max;

            /**
             * Find the optimal threshold
             */
            int best_threshold = -1;
            double best_fuzzyness = std::numeric_limits<double>::infinity();

            for(int threshold = hist_min; threshold <= hist_max; ++threshold) {
                const auto sum = cumulative_histogram.get_count(colors::mask(threshold));
                const auto sum_inv = cumulative_histogram.get_count(colors::mask(max_value)) - cumulative_histogram.get_count(colors::mask(threshold));
                const auto weight = weighted_histogram.get_count(colors::mask(threshold));
                const auto weight_inv = weighted_histogram.get_count(colors::mask(max_value)) - weighted_histogram.get_count(colors::mask(threshold));

                if(sum == 0 || sum_inv == 0)
                    continue;

                const auto mu_0 = std::round(weight / sum);
                const auto mu_1 = std::round(weight_inv / sum_inv);

                const auto fuzzyness = huang_shannon_fuzzyness(hist, threshold, mu_0, mu_1, t_img.get_size());

                if(fuzzyness < best_fuzzyness) {
                    best_fuzzyness = fuzzyness;
                    best_threshold = threshold;
                }
            }

            t_img << binarize::threshold(colors::mask(static_cast<uchar>(best_threshold)));
        };
    }

//    /**
//     * Applies automatic thresholding proposed by Huang et. al.
//     * This implementation uses the measurement of fuzzyness based on the Shannon function.
//     *
//     * Ported from Fiji plugin "Auto Threshold" by Gabriel Landini
//     * https://github.com/fiji/Auto_Threshold/blob/master/src/main/java/fiji/threshold/Auto_Threshold.java
//     *
//     * Liang-Kai Huang and Mao-Jiun J. Wang,
//     * “Image Thresholding by Minimizing the Measures of Fuzziness,”
//     * Pattern Recognition 28, no. 1 (January 1, 1995): 41–51,
//     * https://doi.org/10.1016/0031-3203(94)E0043-K.
//     *
//     * @param t_threshold
//     * @return
//     */
//    inline auto huang_shannon2() {
//        return [](images::mask &t_img) {
//            const auto hist = statistics::get_histogram<statistics::map_vectormap >(t_img);
//            const auto hist_min = misaxx::utils::math::histogram::smallest_key(hist);
//            const auto hist_max = misaxx::utils::math::histogram::largest_key(hist);
//
//            if(hist_min == hist_max) {
//                t_img << values::set(colors::mask::foreground());
//                return;
//            }
//
//            auto threshold = misaxx::utils::math::thresholding::huang_shannon2(histogram.get_data());
//            t_img << binarize::threshold(colors::mask(static_cast<uchar>(threshold)));
//        };
//    }

    /**
     * Applies automatic thresholding proposed by Huang et. al.
     * This implementation uses the measurement of fuzzyness by Yager
     *
     * Liang-Kai Huang and Mao-Jiun J. Wang,
     * “Image Thresholding by Minimizing the Measures of Fuzziness,”
     * Pattern Recognition 28, no. 1 (January 1, 1995): 41–51,
     * https://doi.org/10.1016/0031-3203(94)E0043-K.
     *
     * @param t_threshold
     * @return
     */
    inline auto huang_yager(const double p = 2) {
        return [p](images::mask &t_img) {

            using namespace huang;

            /**
        * Build the necessary histograms for the calculations
        */
            auto hist = statistics::get_histogram(t_img);
            const uchar hist_min = hist.get_min_key();
            const uchar hist_max = hist.get_max_key();

            if(hist_min == hist_max) {
                t_img << values::set(colors::mask::foreground());
                return;
            }

            auto cumulative_histogram = wrapping_cumulative_histogram<colors::mask>(hist);
            auto weighted_histogram = wrapping_weighted_cumulative_histogram<colors::mask>(hist);

            const auto max_value = hist_max;

            /**
             * Find the optimal threshold
             */
            int best_threshold = -1;
            double best_fuzzyness = std::numeric_limits<double>::infinity();

            for(int threshold = hist_min; threshold <= hist_max; ++threshold) {
                const auto sum = cumulative_histogram.get_count(colors::mask(threshold));
                const auto sum_inv = cumulative_histogram.get_count(colors::mask(max_value)) - cumulative_histogram.get_count(colors::mask(threshold));
                const auto weight = weighted_histogram.get_count(colors::mask(threshold));
                const auto weight_inv = weighted_histogram.get_count(colors::mask(max_value)) - weighted_histogram.get_count(colors::mask(threshold));

                if(sum == 0 || sum_inv == 0)
                    continue;

                const auto mu_0 = std::round(weight / sum);
                const auto mu_1 = std::round(weight_inv / sum_inv);

                const auto fuzzyness = huang_yager_fuzzyness(hist, threshold, mu_0, mu_1, t_img.get_size(), p);

                if(fuzzyness < best_fuzzyness) {
                    best_fuzzyness = fuzzyness;
                    best_threshold = threshold;
                }
            }

            t_img << binarize::threshold(colors::mask(static_cast<uchar>(best_threshold)));
        };
    }

}
