/**
 * Copyright by Ruman Gerst
 * Research Group Applied Systems Biology - Head: Prof. Dr. Marc Thilo Figge
 * https://www.leibniz-hki.de/en/applied-systems-biology.html
 * HKI-Center for Systems Biology of Infection
 * Leibniz Institute for Natural Product Research and Infection Biology - Hans Knöll Insitute (HKI)
 * Adolf-Reichwein-Straße 23, 07745 Jena, Germany
 *
 * This code is licensed under BSD 2-Clause
 * See the LICENSE file provided with this code for the full license.
 */

#pragma once

#include <misaxx/core/patterns/misa_file_pattern.h>
#include <misaxx/core/patterns/misa_file_stack_pattern.h>

namespace misaxx::imaging {
    /**
     * File pattern with predefined extensions that cover common image formats
     */
    struct misa_image_stack_pattern : public misaxx::misa_file_stack_pattern {

        misa_image_stack_pattern();

        void from_json(const nlohmann::json &t_json) override;

        std::string get_documentation_name() const override;

        std::string get_documentation_description() const override;

    protected:
        void build_serialization_id_hierarchy(std::vector<misaxx::misa_serialization_id> &result) const override;
    };

    inline void to_json(nlohmann::json& j, const misa_image_stack_pattern& p) {
        p.to_json(j);
    }

    inline void from_json(const nlohmann::json& j, misa_image_stack_pattern& p) {
        p.from_json(j);
    }
}
