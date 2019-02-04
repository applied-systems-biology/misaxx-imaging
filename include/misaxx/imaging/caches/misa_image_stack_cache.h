//
// Created by rgerst on 17.08.18.
//


#pragma once

#include <misaxx/core/descriptions/misa_file_stack_description.h>
#include <misaxx/core/patterns/misa_file_stack_pattern.h>
#include <misaxx/imaging/patterns/misa_image_stack_pattern.h>
#include <misaxx/core/misa_cache.h>
#include <misaxx/imaging/accessors/misa_image_file.h>
#include <misaxx/core/misa_default_cache.h>
#include <misaxx/imaging/descriptions/misa_image_stack_description.h>

namespace misaxx::imaging {

    /**
     * Stack of images stored in a misa_image_stack
     */
    using misa_image_stack_t = std::unordered_map<std::string, misa_image_file>;

    /**
     * Simple stack of images
     */
    struct misa_image_stack_cache : public misaxx::misa_default_cache<misaxx::utils::memory_cache<misa_image_stack_t>,
    misa_image_stack_pattern, misa_image_stack_description> {

        void do_link(const misa_image_stack_description &t_description) override;

    protected:

        misa_image_stack_description produce_description(const boost::filesystem::path &t_location, const misa_image_stack_pattern &t_pattern) override;

    };
}
