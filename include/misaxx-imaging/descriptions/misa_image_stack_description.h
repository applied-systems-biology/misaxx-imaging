//
// Created by ruman on 20.01.19.
//

#pragma once

#include <misaxx/descriptions/misa_file_stack_description.h>

namespace misaxx_imaging {
    struct misa_image_stack_description : public misaxx::misa_file_stack_description {
        using misaxx::misa_file_stack_description::misa_file_stack_description;

    protected:
        void build_serialization_id_hierarchy(std::vector<misaxx::misa_serialization_id> &result) const override;
    };

    inline void to_json(nlohmann::json& j, const misa_image_stack_description& p) {
        p.to_json(j);
    }

    inline void from_json(const nlohmann::json& j, misa_image_stack_description& p) {
        p.from_json(j);
    }
}



