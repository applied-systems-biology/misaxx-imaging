//
// Created by rgerst on 25.01.19.
//


#pragma once
#include <misaxx/imaging/utils/cv2/BMat.h>

namespace cv {
    /**
     * Base class for all static Mats
     * @tparam T 
     * @tparam OpenCVType
     * @tparam Base Any class that supports the BMat constructors
     */
    template<typename T, int OpenCVType, class Derived, class Base = BMat> struct SMat : public Base {
        using static_data_type = T;
        static constexpr int static_opencv_type = OpenCVType;

        SMat() = default;

        explicit SMat(const cv::Size &size, static_data_type init) : Base(size, static_opencv_type, cv::Scalar(init)){
        }

        explicit SMat(cv::Mat mat) : Base(std::move(mat)) {
            if(this->type() != static_opencv_type) {
                throw std::runtime_error("Tried to initialize images Mat from incompatible type!");
            }
        }

        explicit SMat(Base mat) : Base(std::move(mat)) {
            if(this->type() != static_opencv_type) {
                throw std::runtime_error("Tried to initialize images Mat from incompatible type!");
            }
        }

        static_data_type *static_ptr(int row) {
            return this->template ptr<static_data_type >(row);
        }

        const static_data_type *static_ptr(int row) const {
            return this->template ptr<static_data_type >(row);
        }

        static_data_type &static_at(const cv::Point &pos) {
            return this->template at<static_data_type >(pos);
        }

        const static_data_type &static_at(const cv::Point &pos) const {
            return this->template at<static_data_type >(pos);
        }

        Derived clone() const {
            auto copy = Base::clone();
            return Derived(std::move(copy));
        }

    };
}
