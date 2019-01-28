//
// Created by rgerst on 25.01.19.
//

#include <misaxx/imaging/utils/cv2/toolbox/toolbox_statistics.h>

namespace {
    template<typename T> bool is_dynamic_type(const cv::images::buffered &img) {
        return dynamic_cast<const T*>(&img) != nullptr;
    }

    template<typename T> std::unordered_map<double, double>
    get_percentiles_impl(const cv::images::generic &img, const std::vector<double> &percentiles) {
        std::unordered_map<double, double> result;

        // Fetch the values
        std::vector<T> pixels;
        pixels.reserve(img.rows * img.cols);

        for(int row = 0; row < img.rows; ++row) {
            const auto *ptr = img.ptr<T>(row);
            for(int col = 0; col < img.cols; ++col) {
                pixels.push_back(ptr[col]);
            }
        }

        std::unordered_map<double, int> ranks;
        ranks.reserve(percentiles.size());

        for(double percentile : percentiles) {
            if(percentile < 0.0 || percentile > 100.0)
                throw std::runtime_error("Invalid percentile " + std::to_string(percentile));
            auto rank = static_cast<int>(std::ceil(percentile / 100.0 * pixels.size()));
            ranks[percentile] = rank;
        }

        // Naive way is to use std::sort (full sorting) O(n*log n)
        // We use nth_element if we have only 1 element, otherwise we partially sort until the highest rank
        if(percentiles.size() > 1) {
            int reference_rank = -1;
            for(const auto &kv : ranks) {
                if(kv.second > reference_rank)
                    reference_rank = kv.second;
            }
            std::partial_sort(pixels.begin(), pixels.begin() + reference_rank, pixels.end());

            for(const auto &kv : ranks) {
                result[kv.first] = pixels[kv.second];
            }
        }
        else {
            for(const auto &kv : ranks) {
                std::nth_element(pixels.begin(), pixels.begin() + kv.second, pixels.end());
                result[kv.first] = pixels[kv.second];
            }
        }

        return result;
    }
}

cv::toolbox::min_max_result cv::toolbox::statistics::min_max_loc(const cv::images::grayscale &img) {
    using namespace cv::toolbox;
    min_max_result result;
    cv::minMaxLoc(img, &result.min.value, &result.max.value, &result.min.location, &result.max.location);
    return result;
}

std::unordered_map<double, double>
cv::toolbox::statistics::get_percentiles(const cv::images::grayscale &img, const std::vector<double> &percentiles) {
    if(is_dynamic_type<images::grayscale8u >(img)) {
        return get_percentiles_impl<uchar>(img, percentiles);
    }
    else if(is_dynamic_type<images::grayscale8s >(img)) {
        return get_percentiles_impl<char>(img, percentiles);
    }
    else if(is_dynamic_type<images::grayscale16u >(img)) {
        return get_percentiles_impl<ushort>(img, percentiles);
    }
    else if(is_dynamic_type<images::grayscale16s >(img)) {
        return get_percentiles_impl<short>(img, percentiles);
    }
    else if(is_dynamic_type<images::grayscale32s >(img)) {
        return get_percentiles_impl<int>(img, percentiles);
    }
    else if(is_dynamic_type<images::grayscale32f >(img)) {
        return get_percentiles_impl<float>(img, percentiles);
    }
    else if(is_dynamic_type<images::grayscale64f >(img)) {
        return get_percentiles_impl<double>(img, percentiles);
    }
    else {
        throw std::runtime_error("Unsupported image type!");
    }
}

double cv::toolbox::statistics::get_percentile(const cv::images::grayscale &img, double percentile) {
    return get_percentiles(img, { percentile }).begin()->second;
}
