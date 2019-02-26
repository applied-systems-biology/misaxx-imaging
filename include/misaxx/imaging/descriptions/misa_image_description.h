//
// Created by ruman on 20.01.19.
//

#pragma once

#include <misaxx/core/descriptions/misa_file_description.h>

namespace misaxx::imaging {
    struct misa_image_description : public misaxx::misa_file_description {
        using misaxx::misa_file_description::misa_file_description;

    protected:
        void build_serialization_id_hierarchy(std::vector<misaxx::misa_serialization_id> &result) const override;

    public:
        std::string get_documentation_name() const override;

        std::string get_documentation_description() const override;
    };

    inline void to_json(nlohmann::json& j, const misa_image_description& p) {
        p.to_json(j);
    }

    inline void from_json(const nlohmann::json& j, misa_image_description& p) {
        p.from_json(j);
    }

    std::string misa_image_description::get_documentation_name() const {
        return "Image";
    }

    std::string misa_image_description::get_documentation_description() const {
        return "An image file";
    }
}



