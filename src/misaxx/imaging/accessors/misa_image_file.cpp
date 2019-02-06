//
// Created by rgerst on 28.11.18.
//

#include <misaxx/imaging/accessors/misa_image_file.h>

cv::Mat misaxx::imaging::misa_image_file::clone() const {
    return this->access_readonly().get().clone();
}

void misaxx::imaging::misa_image_file::write(cv::Mat t_data) {
    this->access_write().set(std::move(t_data));
}
