//
// Created by rgerst on 28.01.19.
//


#pragma once

#include <misaxx/imaging/utils/cv2/ReadableBMatTypes.h>

namespace cv {
    template<typename T, class ...Rows> struct labeled_image_properties {
        struct row : public Rows... {
        };

        std::unordered_map<int, row> rows;

        explicit labeled_image_properties(const images::labels &labels, const cv::Mat &img) {
            if(labels.size() != img.size())
                throw std::runtime_error("Labels and labeled image must have same size!");
            for(int i = 0; i < labels.rows; ++i) {
                const auto *row = labels[i];
                const T* row2 = img.ptr<T>(i);
                for(int j = 0; j < labels.cols; ++j) {
                    update<Rows...>(j, i, row[j], row2[j]);;
                }
            }
        }

        template<class Row, class ...Args>
        void update(int x, int y, int label, T value) {
            this->template get<Row>(label).update(x, y, label, value);
            if constexpr(sizeof...(Args) > 0) {
                update<Args...>(x, y, label, value);
            }
        }

        template<class Row> Row &get(int label) {
            return dynamic_cast<Row&>(rows[label]);
        }

        template<class Row> const Row &get(int label) const {
            return dynamic_cast<const Row&>(rows.at(label));
        }
    };
}
