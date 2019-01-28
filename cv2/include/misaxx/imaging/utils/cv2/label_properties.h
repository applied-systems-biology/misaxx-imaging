//
// Created by rgerst on 28.01.19.
//


#pragma once

#include <misaxx/imaging/utils/cv2/static_types.h>

namespace cv {
    template<class ...Rows> struct label_properties {

        struct row : public Rows... {
        };

        std::unordered_map<int, row> rows;

        explicit label_properties(const images::labels &labels) {
            for(int i = 0; i < labels.rows; ++i) {
                const auto *row = labels.static_ptr(i);
                for(int j = 0; j < labels.cols; ++j) {
                    update<Rows...>(j, i, row[j]);
                }
            }
        }

        template<class Row, class ...Args>
        void update(int x, int y, int label) {
            this->template get<Row>(label).update(x, y, label);
            if constexpr(sizeof...(Args) > 0) {
                update<Args...>(x, y, label);
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
