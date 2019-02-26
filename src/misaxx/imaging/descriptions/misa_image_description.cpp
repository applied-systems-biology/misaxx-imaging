//
// Created by ruman on 20.01.19.
//

#include <misaxx/imaging/descriptions/misa_image_description.h>

std::string misaxx::imaging::misa_image_description::get_documentation_name() const {
    return "Image";
}

std::string misaxx::imaging::misa_image_description::get_documentation_description() const {
    return "An image file";
}

void misaxx::imaging::misa_image_description::build_serialization_id_hierarchy(
        std::vector<misaxx::misa_serialization_id> &result) const {
    misa_file_description::build_serialization_id_hierarchy(result);
    result.emplace_back(misaxx::misa_serialization_id("misa-imaging", "descriptions/image"));
}
