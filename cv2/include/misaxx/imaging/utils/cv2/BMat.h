//
// Created by rgerst on 25.01.19.
//

#pragma once

#include <opencv2/opencv.hpp>
#include <optional>

namespace cv {
    /**
     * OpenCV Mat with an additional buffer
     */
    class BMat : public cv::Mat {
    public:

        BMat() = default;

        virtual ~BMat() = default;

        /**
         * Initializes a new BMat of given size, type and init value
         * @param size
         * @param type
         * @param init
         */
        explicit BMat(const cv::Size &size, int type, const cv::Scalar &init);

        /**
         * Initializes a new BMat from an existing Mat
         * @param mat
         */
        explicit BMat(cv::Mat mat);

        /**
         * Swaps the buffer and the data of this image
         */
        void swap();

        /**
         * Returns the buffer Mat
         * @param nonEmpty If true and there is no buffer, allocate space for the buffer
         * @return
         */
        cv::Mat &buffer(bool nonEmpty = true);

        /**
         * Adapter to the underlying front cv::Mat (use this with assignment operators)
         * @return
         */
        cv::Mat &self();

        /**
         * Creates a new BMat without initializing it with values
         * @param size
         * @param type
         * @return
         */
        static BMat allocate(const cv::Size &size, int type);

        /**
         * Applies filter in function to this Mat
         * @tparam _Func
         * @param f
         */
        template<class _Func> void swap_after(const _Func &f) {
            f(*this);
            swap();
        }

    private:
        cv::Mat m_buffer;
    };
}



