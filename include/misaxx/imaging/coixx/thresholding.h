//
// Created by rgerst on 21.11.18.
//


#pragma once
#include <vector>
#include <cmath>
#include <misaxx/imaging/coixx/histogram.h>

namespace coixx::math {
    /**
   * Calculates Otsu threshold from a histogram.
   * Legacy function until misaxx::utils::math::histogram will take over
   * @tparam T
   * @param t_histogram
   * @return
   */
    template<class C> inline C otsu(const histogram<C> &t_histogram) {

        int histogram_sum = t_histogram.get_sum();

        // i cumulative p-histogram for the means
        double cumulative_i_p_sum = 0;

        for(const C&t : t_histogram.get_keys()) {
            cumulative_i_p_sum += t * 1.0 * t_histogram.get_count(t);
        }

        cumulative_i_p_sum *= 1.0 / histogram_sum;

        // Initial values for t < 0
        C t_best = C::first_value;
        double var_best = 0;
        double w0 = 0;
        double mu0 = 0;

        for(const C&t : t_histogram.get_keys()) {

            // This cannot change the threshold
            if (t_histogram.get_count(t) == 0)
                continue;

            double p_i = 1.0 * t_histogram.get_count(t) / histogram_sum;
            mu0 *= w0;
            w0 += p_i;
            double w1 = 1.0 - w0;

            mu0 = (mu0 + t * p_i) / w0;
            double mu1 = (cumulative_i_p_sum - w0 * mu0) / w1;
            double var = w0 * w1 * std::pow(mu0 - mu1, 2.0);

            if (var > var_best) {
                var_best = var;
                t_best = t;
            }
        }

        return t_best;
    }

    template<class C>
    inline C huang_shannon2(const std::vector<C> &data) {

        int threshold = -1;
        int ih, it;
        int first_bin;
        int last_bin;
        int sum_pix;
        int num_pix;
        double term;
        double ent;  // entropy
        double min_ent; // min entropy
        double mu_x;

        const auto data_size = static_cast<int>(data.size());

        /* Determine the first non-zero bin */
        first_bin = 0;
        for (ih = 0; ih < data_size; ih++) {
            if (data[ih] != 0) {
                first_bin = ih;
                break;
            }
        }

        /* Determine the last non-zero bin */
        last_bin = data_size - 1;
        for (ih = data_size - 1; ih >= first_bin; ih--) {
            if (data[ih] != 0) {
                last_bin = ih;
                break;
            }
        }
        term = 1.0 / (double) (last_bin - first_bin);
        std::vector<double> mu_0(data_size, 0);

        sum_pix = num_pix = 0;
        for (ih = first_bin; ih < data_size; ih++) {
            sum_pix += ih * data[ih];
            num_pix += data[ih];
            /* NUM_PIX cannot be zero ! */
            mu_0[ih] = sum_pix / (double) num_pix;
        }

        std::vector<double> mu_1(data_size, 0);
        sum_pix = num_pix = 0;
        for (ih = last_bin; ih > 0; ih--) {
            sum_pix += ih * data[ih];
            num_pix += data[ih];
            /* NUM_PIX cannot be zero ! */
            mu_1[ih - 1] = sum_pix / (double) num_pix;
        }

        /* Determine the threshold that minimizes the fuzzy entropy */
        threshold = -1;
        min_ent = std::numeric_limits<double>::infinity();
        for (it = 0; it < data_size; it++) {
            ent = 0.0;
            for (ih = 0; ih <= it; ih++) {
                /* Equation (4) in Ref. 1 */
                mu_x = 1.0 / (1.0 + term * std::abs(ih - mu_0[it]));
                if (!((mu_x < 1e-06) || (mu_x > 0.999999))) {
                    /* Equation (6) & (8) in Ref. 1 */
                    ent += data[ih] * (-mu_x * std::log(mu_x) - (1.0 - mu_x) * std::log(1.0 - mu_x));
                }
            }

            for (ih = it + 1; ih < data_size; ih++) {
                /* Equation (4) in Ref. 1 */
                mu_x = 1.0 / (1.0 + term * std::abs(ih - mu_1[it]));
                if (!((mu_x < 1e-06) || (mu_x > 0.999999))) {
                    /* Equation (6) & (8) in Ref. 1 */
                    ent += data[ih] * (-mu_x * std::log(mu_x) - (1.0 - mu_x) * std::log(1.0 - mu_x));
                }
            }
            /* No need to divide by NUM_ROWS * NUM_COLS * LOG(2) ! */
            if (ent < min_ent) {
                min_ent = ent;
                threshold = it;
            }
        }

        return static_cast<C>(threshold);

    }
}