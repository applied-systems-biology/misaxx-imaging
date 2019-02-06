//
// Created by rgerst on 30.10.18.
//


#pragma once

#include <misaxx/core/misa_cache.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <misaxx/core/misa_cache.h>
#include <misaxx/imaging/patterns/misa_image_pattern.h>
#include <misaxx/imaging/patterns/misa_image_stack_pattern.h>
#include <misaxx/core/misa_default_cache.h>
#include <misaxx/imaging/descriptions/misa_image_description.h>
#include <opencv2/opencv.hpp>

namespace misaxx::imaging {

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
            m_value = cv::imread(m_path.string(), cv::IMREAD_UNCHANGED);
        }

        void stash() override {
            m_value = Image();
        }

        void push() override {
            cv::imwrite(m_path.string(), m_value);
        }

        void do_link(const misa_image_description &t_description) override {
            if(t_description.filename.empty())
                throw std::runtime_error("Cannot link to file description with empty file name!");
            m_path = this->get_location() / t_description.filename;
            this->set_unique_location(m_path);
        }

    protected:

        misa_image_description produce_description(const boost::filesystem::path &t_location, const misa_image_pattern &t_pattern) override {
            misa_image_description result;
            t_pattern.apply(result, t_location);
            return result;
        }

    private:
        Image m_value;
        bool m_has_value = false;
        boost::filesystem::path m_path;
    };
}
