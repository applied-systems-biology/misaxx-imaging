//
// Created by rgerst on 28.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/toolbox/toolbox.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_blur.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_edge.h>

namespace coixx::toolbox::blob {

    /**
    * Calculates a LoG kernel
    * @param t_size
    * @param t_sigma
    * @param t_normalize Normalize with sigma^2
    * @return
    */
    template<class C> inline image<C> laplacian_of_gaussian_kernel(int t_size, double t_sigma, bool t_normalize = true) {

        const float norm = t_normalize ? std::pow(t_sigma, 2) : 1;

        image<C> kernel(cv::Size(t_size, t_size), C::black());
        for(int y = 0; y < kernel.get_height(); ++y) {
            auto * row = kernel.row_ptr(y);
            for(int x = 0; x < kernel.get_width(); ++x) {

                const int cx = x - (kernel.get_width() / 2);
                const int cy = y - (kernel.get_height() / 2);

                row[x].value = norm * -1.0 / (M_PI * pow(t_sigma, 4)) *
                                            (1.0 - (pow(cx, 2) + pow(cy, 2)) / (2.0 * pow(t_sigma, 2))) *
                                            exp(-(pow(cx, 2) + pow(cy, 2)) / (2.0 * pow(t_sigma, 2)));
            }
        }

        return kernel;
    }

    /**
     * Applies blob detection using determinant of hessian
     * Only floating point images are supported
     * @param t_sigma
     * @return
     */
    inline auto determinant_of_hessian(double t_sigma) {
        return [=](auto &t_img) {
            static_assert(traits::is_grayscale(t_img) && traits::is_floating_grayscale_image(t_img), "Image must be floating point grayscale!");

            // Create scale space representation
            t_img << blur::gauss(t_sigma);

            // Get derivations in each direction
            t_img << edge::sobel(2, 0);
            images::raw dxx = t_img.get_mat().clone();
            std::swap(t_img.get_mat(), t_img.get_buffer_mat());
            t_img << edge::sobel(0, 2);
            images::raw dyy = t_img.get_mat().clone();
            std::swap(t_img.get_mat(), t_img.get_buffer_mat());
            t_img << edge::sobel(1, 1);
            images::raw dxy = t_img.get_mat().clone();
            std::swap(t_img.get_mat(), t_img.get_buffer_mat()); // Back to original image

            t_img.get_buffer_mat() = pow(t_sigma, 2) * (dxx.mul(dyy) - dxy.mul(dxy));
            std::swap(t_img.get_mat(), t_img.get_buffer_mat());

        };
    }

    /**
     * Applies blob detection LoG.
     * The kernel size is floor(6 * sigma)
     * @param t_sigma
     * @param t_normalize
     * @return
     */
    inline auto laplacian_of_gaussian( double t_sigma, bool t_normalize = true) {
        return [=](auto &t_img) {
            static_assert(traits::is_grayscale(t_img) && traits::is_floating_grayscale_image(t_img), "Image must be floating point grayscale!");
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_type = typename image_t::color_type;

            const int kernel_size = static_cast<int>(6 * t_sigma);
            const auto kernel = laplacian_of_gaussian_kernel<color_type>(kernel_size, t_sigma, t_normalize);
            cv::filter2D(t_img.get_mat(), t_img.get_buffer_mat(), t_img.get_open_cv_type(), kernel.get_mat());
            std::swap(t_img.get_mat(), t_img.get_buffer_mat());
        };
    }

}
