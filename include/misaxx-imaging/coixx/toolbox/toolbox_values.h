//
// Created by rgerst on 25.06.18.
//


#pragma once

#include <type_traits>
#include <misaxx-imaging/coixx/toolbox/toolbox.h>
#include <misaxx-imaging/coixx/pixel.h>

namespace coixx::toolbox::values {

    /**
     * Inverts the colors in the image
     * @return
     */
    inline auto invert() {
        return [](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;

            if constexpr(traits::is_integral_grayscale_image(t_img)) {
                cv::bitwise_not(t_img.get_image(), t_img.get_image_buffer().get_image());
                t_img.apply_buffer();
            }
            else {
                t_img.get_image() = image_t::color_type::last_value.as_vec() - t_img.get_image();
            }
        };
    }

    /**
     * Sets the color of the whole image
     * @tparam C
     * @param t_color
     * @return
     */
    template<class C> inline auto set(const C &t_color) {
        return[&](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            static_assert(std::is_same<typename image_t::color_type, C>::value, "The provided color and the image color are different!");
            images::raw &raw_image = t_img.get_image();
            raw_image.setTo(t_color.as_vec());
        };
    }

    /**
     * Sets the color of the image by a function
     * @tparam C
     * @tparam Function Function that takes a cv::Point and outputs a color of type C
     * @param t_color
     * @param t_function
     * @return
     */
    template<class Function> inline auto set_by(const Function &t_function) {
        return[&](auto &t_img) {
            if constexpr (traits::is_grayscale(t_img)) {
                for(int y = 0; y < t_img.get_height(); ++y) {
                    auto *row = t_img.row_ptr(y);
                    for(int x = 0; x < t_img.get_width(); ++x) {
                        row[x] = t_function(cv::Point(x, y));
                    }
                }
            }
            else {
                for(int y = 0; y < t_img.get_height(); ++y) {
                    for(int x = 0; x < t_img.get_width(); ++x) {
                        t_img.at(y, x) = t_function(cv::Point(x, y));
                    }
                }
            }
        };
    }

    /**
     * Sets the color in the image to the specified value where the mask applies
     * @tparam C
     * @param t_color
     * @param t_mask
     * @return
     */
    template<class C> inline auto set_where(const C &t_color, const images::mask &t_mask) {
        return[&](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            static_assert(std::is_same<typename image_t::color_type, C>::value, "The provided color and the image color are different!");
            images::raw &raw_image = t_img.get_image();

            if(t_img.get_size() != t_mask.get_size()) {
                throw std::runtime_error("Mask and image must have same size!");
            }
            if(raw_image.type() != t_img.get_open_cv_type()) {
                throw std::runtime_error("Not same type!");
            }
            raw_image.setTo(t_color.as_vec(), t_mask.get_image());
        };
    }

    /**
     * Sets the color in the image to the specified value where the mask does not apply
     * @tparam C
     * @param t_color
     * @param t_mask
     * @return
     */
    template<class C> inline auto set_where_not(const C &t_color, const images::mask &t_mask) {
        return[&](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            static_assert(std::is_same<typename image_t::color_type, C>::value, "The provided color and the image color are different!");

            if(t_img.get_size() != t_mask.get_size()) {
                throw std::runtime_error("Mask and image must have same size!");
            }

            for(int y = 0; y < t_img.get_height(); ++y) {
                auto *row = t_img.row_ptr(y);
                const auto *row_mask = t_mask.row_ptr(y);

                for(int x = 0; x < t_img.get_width(); ++x) {
                    row[x] = row_mask[x] == colors::mask::background() ? t_color : row[x];
                }
            }
        };
    }

    /**
     * Extracts pixels from the image and inserts them using an inserter
     * @tparam C
     * @tparam Inserter Inserter into collection of pixel<C>, C or C::raw_type
     * @param t_inserter
     * @return
     */
    template<class Inserter> inline auto get(Inserter t_inserter) {
        return [t_inserter](const auto &t_img) {

            using image_t = typename std::remove_reference<decltype(t_img)>::type ;
            using color_t = typename image_t::color_type;

            auto it = t_inserter;

            for(int y = 0; y < t_img.get_height(); ++y) {
                auto *row = t_img.row_ptr(y);

                for(int x = 0; x < t_img.get_width(); ++x) {
                    it = pixel<color_t>(x, y, color_t(row[x]));
                }
            }
        };
    }

    /**
     * Extracts pixels from the image and inserts them using an inserter
     * @tparam C
     * @tparam Inserter Inserter into collection of pixel<C>, C or C::raw_type
     * @param t_inserter
     * @return
     */
    template<class Inserter> inline auto get_where(Inserter t_inserter, const images::mask &t_mask) {
        return [&t_mask, t_inserter](const auto &t_img) {

            using image_t = typename std::remove_reference<decltype(t_img)>::type ;
            using color_t = typename image_t::color_type;

            auto it = t_inserter;

            for(int y = 0; y < t_img.get_height(); ++y) {
                auto *row = t_img.row_ptr(y);
                const auto *row_mask = t_mask.row_ptr(y);

                for(int x = 0; x < t_img.get_width(); ++x) {
                    if(row_mask[x].is_foreground())
                        it = pixel<color_t>(x, y, color_t(row[x]));
                }
            }
        };
    }

    /**
    * Extracts pixels from the image and inserts them using an inserter
    * @tparam C
    * @tparam Inserter Inserter into collection of pixel<C>, C or C::raw_type
    * @param t_inserter
    * @return
    */
    template<class Inserter> inline auto get_where_not(Inserter t_inserter, const images::mask &t_mask) {
        return [t_inserter, &t_mask](const auto &t_img) {

            using image_t = typename std::remove_reference<decltype(t_img)>::type ;
            using color_t = typename image_t::color_type;

            auto it = t_inserter;

            for(int y = 0; y < t_img.get_height(); ++y) {
                auto *row = t_img.row_ptr(y);
                const auto *row_mask = t_mask.row_ptr(y);

                for(int x = 0; x < t_img.get_width(); ++x) {
                    if(row_mask[x].is_background())
                        it = pixel<color_t>(x, y, color_t(row[x]));
                }
            }
        };
    }

    /**
     * Function that returns true if the input pixel does not have a value of zero (or C::default_value)
     * This includes negative values.
     */
    template<class C> struct if_non_zero_pixel {
        inline bool operator()(const pixel<C> &t_pixel) const {
            return t_pixel.value != C::default_value;
        }
    };

    /**
     * Function that returns true if the input pixel has a value of zero (or C::default_value)
     */
    template<class C> struct if_zero_pixel {
        inline bool operator()(const pixel<C> &t_pixel) const {
            return t_pixel.value == C::default_value;
        }
    };

    /**
     * Extracts pixels from the image if they satisfy some condition defined by a function
     * @tparam C
     * @tparam Inserter
     * @tparam Function Function that takes pixel<C>, C or C::raw_type
     * @param t_inserter
     * @param t_mask
     * @param t_function
     * @return
     */
    template<class Inserter, class Function> inline auto get_if(Inserter t_inserter, const Function &t_function) {
        return [t_inserter, &t_function](const auto &t_img) {

            using image_t = typename std::remove_reference<decltype(t_img)>::type ;
            using color_t = typename image_t::color_type;

            auto it = t_inserter;

            for(int y = 0; y < t_img.get_height(); ++y) {
                auto *row = t_img.row_ptr(y);

                for(int x = 0; x < t_img.get_width(); ++x) {
                    const auto px = pixel<color_t>(x, y, color_t(row[x]));
                    if(t_function(px)) {
                        it = px;
                    }
                }
            }
        };
    }

    /**
     * Backups the image to another image
     * @tparam C
     * @param t_output
     * @return
     */
    template<class C> inline auto backup(image<C> &t_output) {
        return[&](auto &t_img) {
            static_assert(traits::is_compatible<C>(t_img), "Output and input images are incompatible!");

            t_output = t_img.clone();
        };
    }

    /**
     * Clamps the image values between the provided minimum and maximum values.
     * @tparam C
     * @param t_min
     * @param t_max
     * @return
     */
    template<class C> inline auto clamp(C t_min, C t_max) {
        if(t_min.value > t_max.value) {
            throw std::runtime_error("Minimum must be <= the maximum value!");
        }

        auto min = t_min.value;
        auto max = t_max.value;

        return [=](auto &t_img) {
            for(int y = 0; y < t_img.get_height(); ++y) {
                auto *row = t_img.row_ptr(y);
                for(int x  = 0; x < t_img.get_width(); ++x) {
                    row[x].value = row[x].value < min ? min : ( row[x].value > max ? max : row[x].value);
                }
            }
        };
    }

    /**
    * Clamps the image values below the minimum value
    * @tparam C
    * @param t_min
    * @param t_max
    * @return
    */
    template<class C> inline auto clamp_below(C t_min) {

        auto min = t_min;

        return [=](auto &t_img) {
            for(int y = 0; y < t_img.get_height(); ++y) {
                auto *row = t_img.row_ptr(y);
                for(int x  = 0; x < t_img.get_width(); ++x) {
                    row[x] = row[x] < min ? min : row[x];
                }
            }
        };
    }

    /**
    * Clamps the image values above the maximum value
    * @tparam C
    * @param t_min
    * @param t_max
    * @return
    */
    template<class C> inline auto clamp_above(C t_max) {

        auto max = t_max;

        return [=](auto &t_img) {
            for(int y = 0; y < t_img.get_height(); ++y) {
                auto *row = t_img.row_ptr(y);
                for(int x  = 0; x < t_img.get_width(); ++x) {
                    row[x] = row[x] > max ? max : row[x];
                }
            }
        };
    }

    /**
    * Applies absolute value transformation to the values.
    * @return
    */
    inline auto abs() {

        return [](auto &t_img) {
            for(int y = 0; y < t_img.get_height(); ++y) {
                auto *row = t_img.row_ptr(y);
                for(int x  = 0; x < t_img.get_width(); ++x) {
                    row[x] = std::abs(row[x]);
                }
            }
        };
    }



    /**
     * Clamps only the negative part of the image and returns the absolute.
     * Faster equivalent to filter(filter(image, clamp_above(0)), abs())
     * @return
     */
    inline auto negative_part() {
        return [](auto &t_img) {
            return [](auto &t_img) {
                for(int y = 0; y < t_img.get_height(); ++y) {
                    auto *row = t_img.row_ptr(y);
                    for(int x  = 0; x < t_img.get_width(); ++x) {
                        row[x] = std::max(0, -row[x]);
                    }
                }
            };
        };
    }

    /**
     * Equivalent to clamp_below(0)
     * @return
     */
    inline auto positive_part() {
        return [](auto &t_img) {
            return [](auto &t_img) {
                for(int y = 0; y < t_img.get_height(); ++y) {
                    auto *row = t_img.row_ptr(y);
                    for(int x  = 0; x < t_img.get_width(); ++x) {
                        row[x] = std::max(0, row[x]);
                    }
                }
            };
        };
    }

    /**
    * Clamps the image values between the minimum supported value and maximum supported value.
    * @tparam Image
    * @param t_min
    * @param t_max
    * @return
    */
    inline auto clamp() {
        return [](auto &t_img) {
            using image_t = typename std::remove_reference<decltype(t_img)>::type;
            using color_type = typename image_t::color_type;

            t_img << clamp(color_type::first_value, color_type::last_value);
        };
    }
}
