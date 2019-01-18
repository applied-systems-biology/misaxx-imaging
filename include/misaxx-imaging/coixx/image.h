//
// Created by rgerst on 05.06.18.
//


#pragma once

#include <opencv2/core/mat.hpp>
#include <misaxx-imaging/coixx/colors/color_bgr_uint8.h>
#include <misaxx-imaging/coixx/colors/color_hsv_uint8.h>
#include <misaxx-imaging/coixx/colors/color_grayscale_int.h>
#include <misaxx-imaging/coixx/colors/color_grayscale_floating.h>

namespace coixx {
    template<class C>
    class image;

    namespace images {
        using raw = cv::Mat;

        using grayscale8u = image<colors::grayscale8u>;
        using grayscale16u = image<colors::grayscale16u>;
        using grayscale8s = image<colors::grayscale8s>;
        using grayscale16s = image<colors::grayscale16s>;
        using grayscale32s = image<colors::grayscale32s>;
        using grayscale_float = image<colors::grayscale_float>;
        using grayscale_double = image<colors::grayscale_double>;
        using grayscale32f = image<colors::grayscale32f>;
        using grayscale64f = image<colors::grayscale64f>;
        using hsv8u = image<colors::hsv8u >;
        using bgr8u = image<colors::bgr8u >;
        using mask = image<colors::mask>;
        using labels16u = image<colors::labels16u>;
        using labels32s = image<colors::labels32s>;
        using labels = image<colors::labels>;
    }

    template<class C>
    class image {
    public:

        static constexpr int opencv_type = C::opencv_type;
        static constexpr int num_channels = C::channels;

        /**
         * The type that stores the image
         */
        using underlying_image_type = images::raw;

        /**
         * The color space of this image
         */
        using color_type = C;

        image() = default;

        image(const image<C> &t_src) = delete;

        image(image<C> &&t_src) noexcept :
        m_img(t_src.m_img), m_buffer_image(std::move(t_src.m_buffer_image)) {
            t_src.m_img = cv::Mat();
        }

        ~image() = default;

        image<C> &operator =(const image<C> &t_src) = delete;

        image<C> &operator =(image<C> &&t_src) noexcept {
            m_img = t_src.m_img;
            m_buffer_image = std::move(t_src.m_buffer_image);
            t_src.m_img = cv::Mat();
            return *this;
        }

        /**
         * Creates an image of given size
         * Please note that this will not initialize the image
         * @param t_init_color Initializes the image with given color
         * @param t_size
         */
        explicit image(const cv::Size &t_size, const C &t_init_color) : m_img(images::raw(t_size, opencv_type, t_init_color.as_scalar())) {
        }

        /**
         * Constructs a new image from an OpenCV image with given type
         * @param t_img
         * @param t_type
         */
        explicit image(images::raw t_img) : m_img(std::move(t_img)) {
            if (this->get_image().empty()) {
                throw std::runtime_error("The input image is empty!");
            }
            if (this->get_image().type() != opencv_type) {
                throw std::runtime_error("The type of the OpenCV image is not compatible with this image.");
            }
        }

        /**
         * Clones the image and optionally the buffer
         * @param with_buffer
         * @return
         */
        image<C> clone(bool with_buffer = false) const {
            image<C> result;
            result.get_image() = this->get_image().clone();
            if(with_buffer && this->m_buffer_image) {
                result.m_buffer_image = std::make_unique<image<C>>(this->m_buffer_image.get()->clone(with_buffer));
            }

            return result;
        }

        /**
         * Returns a shallow copy of the image, including the buffer
         * @return
         */
        image<C> share() const {
            image<C> result;
            result.m_img = m_img;
            result.m_buffer_image = m_buffer_image;
            return result;
        }

        /**
         * Moves this image into the return value of the function
         * @return
         */
        image<C> move() {
            return std::move(*this);
        }

        /**
         * Allocates a new image without a default color.
         * @param t_size
         * @return
         */
        static image<C> allocate(const cv::Size &t_size) {
            return image<C>(cv::Mat(t_size, opencv_type));
        }

        C *row_ptr(int y) {
            return this->get_image().template ptr<C>(y);
        }

        const C *row_ptr(int y) const {
            return this->get_image().template ptr<C>(y);
        }

        C at(int y, int x) const {
            return this->get_image().template at<C>(y, x);
        }

        C &at(int y, int x) {
            return this->get_image().template at<C>(y, x);
        }

        C at(const cv::Point &t_point) const {
            return this->get_image().template at<C>(t_point);
        }

        C &at(const cv::Point &t_point) {
            return this->get_image().template at<C>(t_point);
        }

        /**
         * Gets the size of the image
         * @return
         */
        inline cv::Size get_size() const {
            return  this->get_image().size();
        }

        /**
         * Gets the width of the image
         * @return
         */
        inline int get_width() const {
            return get_size().width;
        }

        /**
         * Gets the height of the image
         * @return
         */
        inline int get_height() const {
            return get_size().height;
        }

        /**
         * Gets a buffer image
         * @return
         */
        image<C> &get_image_buffer() {
            ensure_buffer_image();
            return *m_buffer_image;
        }

        /**
         * Swaps the buffer image with the unbuffered image
         */
        void apply_buffer() {
            std::swap(m_buffer_image->get_image(), this->get_image());
        }

        /**
         * If the buffer image does not exist, create it
         */
        void ensure_buffer_image() {
            if(!m_buffer_image) {
                m_buffer_image = std::make_unique<image<C>>(get_size(), C(C::default_value));
            }
        }

        /**
         * Deletes the buffer image
         */
        void clear_buffer() {
            m_buffer_image = nullptr;
        }

        /**
         * Convenience wrapper for C::opencv_type
         * @return
         */
        inline int get_open_cv_type() const {
            return C::opencv_type;
        }

        /**
       * Gets the current image as reference
       * @return
       */
        cv::Mat &get_image() {
            return m_img;
        }

        /**
         * Gers the current image as const reference
         * @return
         */
        const cv::Mat &get_image() const {
            return m_img;
        }

//        image<C> &operator =(image<C> &&src) noexcept {
//            m_img = std::move(src.m_img);
//            m_buffer_image = std::move(src.m_buffer_image);
//            return *this;
//        }

        bool is_empty() const {
            return m_img.empty();
        }

    private:

        cv::Mat m_img;
        std::shared_ptr<image<C>> m_buffer_image;

    };
}