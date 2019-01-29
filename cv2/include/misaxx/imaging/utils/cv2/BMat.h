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
        explicit BMat(const cv::Mat &mat);

        /**
         * Swaps the buffer and the data of this image
         */
        void swap();

        /**
         * Clones this buffered Mat.
         * Does not include the buffer
         * @return
         */
        BMat clone() const;

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
    
    /**
     * BMat equivalent to Mat_
     * @tparam _Tp 
     */
    template<typename _Tp> class BMat_ : public BMat {
    public:

        BMat_() = default;

        ~BMat_() override = default;

        /**
         * Initializes a new BMat of given size and init value
         * @param size
         * @param init
         */
        explicit BMat_(const cv::Size &size, const _Tp &init);

        /**
         * Initializes a new BMat from an existing Mat
         * @param mat
         */
        explicit BMat_(const cv::Mat &mat);

        /**
         * Clones this BMat. Does not include the buffer
         * @return
         */
        BMat_<_Tp> clone() const;

        /**
         * Creates a new BMat without initializing it with values
         * @param size
         * @param type
         * @return
         */
        static BMat_<_Tp> allocate(const cv::Size &size);

        //! more convenient forms of row and element access operators
        _Tp* operator [](int y);

        const _Tp* operator [](int y) const;

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

    using BMat1b = BMat_<uchar>;
    using BMat2b = BMat_<Vec2b>;
    using BMat3b = BMat_<Vec3b>;
    using BMat4b = BMat_<Vec4b>;

    using BMat1s = BMat_<short>;
    using BMat2s = BMat_<Vec2s>;
    using BMat3s = BMat_<Vec3s>;
    using BMat4s = BMat_<Vec4s>;

    using BMat1w = BMat_<ushort>;
    using BMat2w = BMat_<Vec2w>;
    using BMat3w = BMat_<Vec3w>;
    using BMat4w = BMat_<Vec4w>;

    using BMat1i = BMat_<int>;
    using BMat2i = BMat_<Vec2i>;
    using BMat3i = BMat_<Vec3i>;
    using BMat4i = BMat_<Vec4i>;

    using BMat1f = BMat_<float>;
    using BMat2f = BMat_<Vec2f>;
    using BMat3f = BMat_<Vec3f>;
    using BMat4f = BMat_<Vec4f>;

    using BMat1d = BMat_<double>;
    using BMat2d = BMat_<Vec2d>;
    using BMat3d = BMat_<Vec3d>;
    using BMat4d = BMat_<Vec4d>;
}

#include <misaxx/imaging/utils/cv2/detail/BMat.h>


