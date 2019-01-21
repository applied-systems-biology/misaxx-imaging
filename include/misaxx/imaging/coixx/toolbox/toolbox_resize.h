//
// Created by rgerst on 23.07.18.
//


#pragma once

#include <misaxx/imaging/coixx/toolbox/toolbox.h>
#include <misaxx/imaging/coixx/margin.h>

namespace coixx::toolbox {

    /**
     * Available resize interpolations
     */
    enum resize_interpolation : int {
        linear = cv::INTER_LINEAR,
        cubic = cv::INTER_CUBIC,
        nearest = cv::INTER_NEAREST
    };

    /**
     * Creates a new image that is a resized copy if this image
     * @param t_size
     * @param t_interpolation
     * @return
     */
    template<class C>
    inline image<C> resize(const image<C> &t_img, const cv::Size &t_size, resize_interpolation t_interpolation) {
        const images::raw &img = t_img.get_image();
        images::raw img_buf(t_size, img.type());
        cv::resize(img, img_buf, t_size, 0, 0, static_cast<int>(t_interpolation));
        return image<C>(img_buf); // TODO: std::move?
    }

    /**
     * Creates a new image that is a resized copy if this image
     * @param t_scale
     * @param t_interpolation
     * @return
     */
    template<class C>
    inline image<C> resize(const image<C> &t_img, double t_scale, resize_interpolation t_interpolation) {
        if (t_scale <= 0) {
            throw std::runtime_error("Invalid scale!");
        }

        return resize(t_img, cv::Size(static_cast<int>(t_img.get_size().width * t_scale),
                                      static_cast<int>(t_img.get_size().height * t_scale)),
                      t_interpolation);
    }

    /**
     * Creates a new image that is an upscaled copy with a constant colored border around it
     * @param t_border
     * @param t_interpolation
     * @param t_border_color
     * @return
     */
    template<class C>
    inline image<C> add_border(const image<C> &t_img, margin t_border, C t_border_color = C()) {

        if (!t_border.is_positive()) {
            throw std::runtime_error("Only positive margins are supported!");
        }

        const images::raw &img = t_img.get_image();

        images::raw target(cv::Size(img.size().width + t_border.get_left() + t_border.get_right(),
                                    img.size().height + t_border.get_top() + t_border.get_bottom()),
                           img.type());
        cv::copyMakeBorder(img,
                           target,
                           t_border.get_top(),
                           t_border.get_bottom(),
                           t_border.get_left(),
                           t_border.get_right(),
                           cv::BORDER_CONSTANT,
                           t_border_color.as_scalar());
        return image<C>(std::move(target));
    }

    /**
     * Creates a new image that is an downscaled copy created by removing the border around the image
     * @param t_border
     * @param t_interpolation
     * @return
     */
    template<class C>
    inline image<C> remove_border(const image<C> &t_img, margin t_border) {

        if (!t_border.is_positive()) {
            throw std::runtime_error("Only positive margins are supported!");
        }

        const images::raw &img = t_img.get_image();
        cv::Rect roi = t_border.to_rect(img.size());
        return image<C>(std::move(img(roi)));
    }

}
