//
// Created by rgerst on 22.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/image.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_statistics.h>

namespace coixx::toolbox::binarize {

    /**
     * Applies Otsu thresholding for each individual component in the image
     * @param t_threshold
     * @return
     */
    inline auto otsu_per_component(const images::grayscale32s &t_components) {
        return [&t_components](images::mask &t_img) {
            if(t_img.get_size() != t_components.get_size()) {
                throw std::runtime_error("Components and image have different sizes!");
            }

            // First collect all histograms
            int component_count = toolbox::statistics::max(t_components) + 1;
            std::vector<std::vector<int>> histograms;
            histograms.reserve(static_cast<size_t>(component_count));
            std::vector<int> histogram_sums(static_cast<size_t>(component_count));

            for(int i = 0; i < component_count; ++i) {
                histograms.emplace_back(std::vector<int>(256));
            }

            for(int y = 0; y < t_img.get_mat().rows; ++y) {

                const colors::labels *row_component = t_components.row_ptr(y);
                const colors::mask *row = t_img.row_ptr(y);

                for(int x = 0; x < t_img.get_mat().cols; ++x) {
                    if(row_component[x].value > 0) {
                        ++(histograms[row_component[x]][row[x]]);
                        ++(histogram_sums[row_component[x]]);
                    }
                }
            }

            // Calculate the threshold for each component (This is the code from image_filter_binarize_otsu2)
            std::vector<int> thresholds(static_cast<size_t>(component_count));

            for(int component = 0; component < component_count; ++component) {
                const std::vector<int> &histogram = histograms[component];
                const int histogram_sum = histogram_sums[component];

                if(histogram_sum == 0) {
                    thresholds[component] = 256;
                    continue;
                }

                // i cumulative p-histogram for the means
                double cumulative_i_p_sum = 0;

                for(int t = 0; t <= 255; ++t) {
                    cumulative_i_p_sum += t * 1.0 * histogram[t];
                }

                cumulative_i_p_sum *= 1.0 / histogram_sum;

                // Initial values for t < 0
                int t_best = 0;
                double var_best = 0;
                double w0 = 0;
                double mu0 = 0;

                for(int t = 0; t <= 255; ++t) {

                    // This cannot change the threshold
                    if(histogram[t] == 0)
                        continue;

                    double p_i = 1.0 * histogram[t] / histogram_sum;
                    mu0 *= w0;
                    w0 += p_i;
                    double w1 = 1.0 - w0;

                    mu0 = (mu0 + t * p_i) / w0;
                    double mu1 = (cumulative_i_p_sum - w0 * mu0) / w1;
                    double var = w0 * w1 * pow(mu0 - mu1, 2);

                    if(var > var_best) {
                        var_best = var;
                        t_best = t;
                    }
                }

                thresholds[component] = t_best;
            }

            // Apply the thresholds to the image
            for(int y = 0; y < t_img.get_mat().rows; ++y) {

                const colors::labels *row_component = t_components.row_ptr(y);
                colors::mask *row = t_img.row_ptr(y);

                for(int x = 0; x < t_img.get_mat().cols; ++x) {
                    if(row_component[x] > 0) {
                        const int threshold = thresholds[row_component[x]];
                        row[x] = row[x] > threshold ? colors::mask::foreground() : colors::mask::background();
                    }
                    else {
                        row[x] = colors::mask::background();
                    }
                }
            }
        };
    }

}
