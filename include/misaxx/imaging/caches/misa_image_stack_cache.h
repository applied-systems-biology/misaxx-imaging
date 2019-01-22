//
// Created by rgerst on 17.08.18.
//


#pragma once

#include <misaxx/imaging/coixx/image.h>
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
    template<class Image> using misa_image_stack_t = std::unordered_map<std::string, misa_image_file<Image>>;

    /**
     * Simple stack of images of cv::Mat or any of coixx::image<T>
     * @tparam Image
     */
    template<class Image> struct misa_image_stack_cache : public misaxx::misa_default_cache<misaxx::utils::memory_cache<misa_image_stack_t<Image>>,
    misa_image_stack_pattern, misa_image_stack_description> {

        using image_type = Image;

        void do_link(const misa_image_stack_description &t_description) override {
            auto &files = this->get();
            for(const auto &kv : t_description.files) {
                misa_image_description description;
                description.filename = kv.second.filename;
                misa_image_file<Image> cache;
                cache.suggest_link(this->get_location(), misaxx::misa_description_storage::with(std::move(description))); // We link manually with the loaded description
                files.insert({ kv.first, cache });
            }

            this->set_unique_location(this->get_location());
        }

    protected:

        misa_image_stack_description produce_description(const boost::filesystem::path &t_location, const misa_image_stack_pattern &t_pattern) override {
            auto stack = t_pattern.produce(t_location);
            misa_image_stack_description result;
            result.files = std::move(stack.files);
            return result;
        }

    };
}
