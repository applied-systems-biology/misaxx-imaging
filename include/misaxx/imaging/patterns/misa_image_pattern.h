//
// Created by rgerst on 02.11.18.
//


#pragma once

#include <misaxx/core/patterns/misa_file_pattern.h>

namespace misaxx::imaging {
    struct misa_image_pattern : public misaxx::misa_file_pattern {
        misa_image_pattern();

    protected:
        void build_serialization_id_hierarchy(std::vector<misaxx::misa_serialization_id> &result) const override;
    };

    inline void to_json(nlohmann::json& j, const misa_image_pattern& p) {
        p.to_json(j);
    }

    inline void from_json(const nlohmann::json& j, misa_image_pattern& p) {
        p.from_json(j);
    }
}
