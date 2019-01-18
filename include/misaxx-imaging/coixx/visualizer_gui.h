//
// Created by rgerst on 27.06.18.
//


#pragma once

#include <misaxx-imaging/coixx/image.h>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <misaxx-imaging/coixx/converters/semantic_convert.h>
#include <misaxx-imaging/coixx/toolbox/toolbox_visualization.h>
#include <misaxx-imaging/coixx/toolbox/toolbox_io.h>

namespace coixx {

    struct show_visualizer_gui {
    };

    /**
     * Tag type that contains the request to save the visualizer_gui images to a directory.
     * Apply it using the << operator.
     *
     * Example:
     *
     * visualizer_gui() << named_image(image, "my image") << show_visualizer_gui();
     */
    struct save_visualizer_gui {
        const boost::filesystem::path directory;

        explicit save_visualizer_gui(boost::filesystem::path t_directory);
    };

    /**
     * Wrapper around HighGUI that allows viewing multiple images.
     * To use it, create an instance of visualizer_gui and insert images using the << operator. The << operator will accept
     * opencv_image instances or named_image()-wrapped images. To show show the GUI, add show_visualizer_gui using the << operator.
     *
     * Example:
     *
     * visualizer_gui() << named_image(image, "my image") << show_visualizer_gui();
     */
    class visualizer_gui {

    public:

        template<class C>
        struct input_image {
            const ::coixx::image<C> &image;
            std::string name;

            explicit input_image(const ::coixx::image<C> &t_image, std::string t_name) : image(t_image), name(std::move(t_name)) {

            }
        };

        template<class C>
        visualizer_gui &visualize(const input_image<C> &t_img) {
            if constexpr (std::is_same<C, colors::grayscale32s>::value) {
                insert(input_image<colors::bgr8u>(coixx::toolbox::visualization::labels(t_img.image), t_img.name));
            } else {
                insert(input_image<colors::bgr8u>(converters::semantic_convert<images::bgr8u>(t_img.image), t_img.name));
            }
            return *this;
        }


        template<class C>
        visualizer_gui &visualize(const image<C> &t_img) {
            return visualize(input_image<C>(t_img, "image " + std::to_string(m_images.size() + 1)));
        }

        visualizer_gui &insert(const images::bgr8u &t_img);

        visualizer_gui &insert(const input_image<colors::bgr8u> &t_img);

    private:

        std::vector<images::bgr8u> m_images;
        std::vector<std::string> m_image_names;

        /**
         * Internal window implementation
         */
        class window {

        private:
            std::string m_window_name;
            std::vector<images::bgr8u> m_images;
            std::vector<std::string> m_image_names;

            static void on_trackbar_change(int index, void *data);

        public:

            explicit window(visualizer_gui &gui);

            /**
             * Switches the current image to given index.
             * @param index
             */
            void switch_to(size_t index);

            /**
             * Shows the window and waits until it closes.
             * Internal function.
             */
            void show_and_wait();

        };

    public:

        /**
         * Shows the visualizer_gui window and waits until the user closes the window
         */
        void show_and_wait();

        /**
         * Saves all images into the target directory.
         * The filename is <image_index>_<image_name>.tif
         * @param t_target_directory
         * @param t_extension Supported file extension
         */
        void save_images(const boost::filesystem::path &t_target_directory, const std::string &t_extension = ".tif");

    };

    /**
     * Wrapper around visualizer_gui::input_image<C> that creates a named entry to the target visualizer_gui
     * @tparam C
     * @param t_image
     * @param t_name
     * @return
     */
    template<class C>
    inline visualizer_gui::input_image<C> named_image(const image<C> &t_image, const std::string &t_name) {
        return visualizer_gui::input_image<C>(t_image, t_name);
    }

    /**
     * Inserts an image into the visualizer_gui.
     * The name is automatically generated.
     * @tparam C
     * @param sink
     * @param t_image
     * @return
     */
    template<class C>
    inline visualizer_gui &operator<<(visualizer_gui &sink, const image<C> &t_image) {
        return sink.visualize(t_image);
    }

    /**
     * Inserts an image into the visualizer_gui.
     * The name is automatically generated.
     * @tparam C
     * @param sink
     * @param t_image
     * @return
     */
    template<class C>
    inline visualizer_gui operator<<(visualizer_gui &&sink, const image<C> &t_image) {
        sink.visualize(t_image);
        return std::forward<visualizer_gui>(sink);
    }

    /**
     * Inserts a named image into the visualizer_gui
     * @tparam C
     * @param sink
     * @param t_image
     * @return
     */
    template<class C>
    inline visualizer_gui &operator<<(visualizer_gui &sink, const visualizer_gui::input_image<C> &t_image) {
        return sink.visualize(t_image);
    }

    /**
     * Inserts a named image into the visualizer_gui
     * @tparam C
     * @param sink
     * @param t_image
     * @return
     */
    template<class C>
    inline visualizer_gui operator<<(visualizer_gui &&sink, const visualizer_gui::input_image<C> &t_image) {
        sink.visualize(t_image);
        return std::forward<visualizer_gui>(sink);
    }

    /**
     * Shows the visualizer_gui. Wrapper around visualizer_gui::show_and_wait
     * @param sink
     * @param t_tag
     * @return
     */
    inline visualizer_gui &operator<<(visualizer_gui &sink, const show_visualizer_gui &) {
        sink.show_and_wait();
        return sink;
    }

    /**
     * Shows the visualizer_gui. Wrapper around visualizer_gui::show_and_wait
     * @param sink
     * @param t_tag
     * @return
     */
    inline visualizer_gui operator<<(visualizer_gui &&sink, const show_visualizer_gui &) {
        sink.show_and_wait();
        return std::forward<visualizer_gui>(sink);
    }

    /**
     * Saves all images of the visualizer_gui into the directory defined by save_visualizer_gui.
     * @param sink
     * @param t_tag
     * @return
     */
    inline visualizer_gui &operator<<(visualizer_gui &sink, const save_visualizer_gui &t_tag) {
        sink.save_images(t_tag.directory);
        return sink;
    }

    /**
     * Saves all images of the visualizer_gui into the directory defined by save_visualizer_gui.
     * @param sink
     * @param t_tag
     * @return
     */
    inline visualizer_gui operator<<(visualizer_gui &&sink, const save_visualizer_gui &t_tag) {
        sink.save_images(t_tag.directory);
        return std::forward<visualizer_gui>(sink);
    }
}