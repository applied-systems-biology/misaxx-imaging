//
// Created by rgerst on 30.10.18.
//


#pragma once

#include <misaxx/misa_cache.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <misaxx-imaging/coixx/toolbox/toolbox_io.h>
#include <misaxx/misa_cache.h>
#include <misaxx-imaging/patterns/misa_image_pattern.h>
#include <misaxx-imaging/patterns/misa_image_stack_pattern.h>
#include <misaxx/misa_default_cache.h>
#include <misaxx-imaging/descriptions/misa_image_description.h>

namespace misaxx_imaging {

    /**
     * A cache that holds an OpenCV cv::Mat or a coixx::image
     * @tparam Image
     */
    template<class Image> class misa_image_file_cache : public misaxx::misa_default_cache<misaxx::utils::cache<Image>,
            misa_image_pattern, misa_image_description> {
    public:

        Image &get() override {
            return m_value;
        }

        const Image &get() const override {
            return m_value;
        }

        void set(Image value) override {
            m_value = std::move(value);
            m_has_value = true;
        }

        bool has() const override {
            return m_has_value;
        }

        bool can_pull() const override {
            return boost::filesystem::is_regular_file(m_path);
        }

        void pull() override {
            if constexpr (std::is_same<cv::Mat, Image>::value) {
                // Load it as cv::Mat
                m_value = cv::imread(m_path.string(), cv::IMREAD_UNCHANGED);
            }
            else {
                // Assume it's a coixx::image
                m_value = coixx::toolbox::auto_load<Image>(m_path);
            }
        }

        void stash() override {
            m_value = Image();
        }

        void push() override {
            if constexpr (std::is_same<cv::Mat, Image>::value) {
                cv::imwrite(m_path.string(), m_value);
            }
            else {
                using namespace coixx::toolbox;
                m_value << save(m_path);
            }
        }

        void do_link(const misa_image_description &t_description) override {
            if(t_description.filename.empty())
                throw std::runtime_error("Cannot link to file description with empty file name!");
            m_path = this->get_location() / t_description.filename;
            this->set_unique_location(m_path);
        }

    protected:

        misa_image_description produce_description(const boost::filesystem::path &t_location, const misa_image_pattern &t_pattern) override {
            auto image = t_pattern.produce(t_location);
            misa_image_description result;
            result.filename = std::move(image.filename);
            return result;
        }

    private:
        Image m_value;
        bool m_has_value = false;
        boost::filesystem::path m_path;
    };
}
