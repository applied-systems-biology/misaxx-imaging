//
// Created by rgerst on 28.11.18.
//

#pragma once

#include <misaxx/core/misa_cached_data.h>
#include <misaxx/imaging/caches/misa_image_file_cache.h>
#include <misaxx/core/misa_default_description_accessors.h>

namespace misaxx::imaging {

    /**
     * A simple 2D image file
     * @tparam Image cv::Mat or any of coixx::image<C>
     */
    template<class Image> struct misa_image_file : public misaxx::misa_cached_data<misa_image_file_cache<Image>>,
                                                   public misaxx::misa_description_accessors_from_cache<misa_image_file_cache<Image>, misa_image_file<Image>> {
        /**
         * Clones the image content read from access_readonly()
         * @return
         */
        Image clone() const {
            return this->access_readonly().get().clone();
        }

        /**
         * Writes image data into the current file
         * @param t_data
         */
        void write(Image t_data) {
            this->access_write().set(std::move(t_data));
        }
    };
}



