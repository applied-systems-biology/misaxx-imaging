//
// Created by rgerst on 23.07.18.
//


#pragma once

#include <misaxx-imaging/coixx/toolbox/toolbox.h>
#include <misaxx-imaging/coixx/image.h>
#include <misaxx-imaging/coixx/objects/label_properties.h>

namespace coixx {

    /**
     * Base class for all object properties.
     * Must be inside of a struct that contains the actual type.
     *
     * Template for custom object_properties:
     * struct my_property {
     *  template<class CLabel, class CImage> struct type : public label_property {
     *      inline void update(int x, int y, CLabel label, CImage value);
     *  }
     * }
     */
    struct object_property {

    };

    /**
     * Calculates properties of each object in the provided image. The objects are defined by a labeling image.
     * @tparam CImage Color of input image
     * @tparam CLabel Color of label image
     * @tparam MapTag misaxx::utils::math::function map tag (e.g. misaxx::utils::math::function::map_hashmap) that indicates which map should be used
     * @tparam PropertyTags Any set of tag structs that contain a sub-type "type" based on object_property_t or multiobject_image_property_t
     */
    template<class CImage, class CLabel = colors::grayscale32s, class ... PropertyTags> struct object_properties {

        struct properties : public PropertyTags::template type<CImage, CLabel>... {

            template<class Tag, class Type = typename Tag::template type<CImage, CLabel>> Type &get() {
                return *this;
            }

            template<class Tag, class Type = typename Tag::template type<CImage, CLabel>> const Type &get() const {
                return *this;
            }

            template<class Tag, class ... SubTags> void update(int x, int y, const CLabel &label, const CImage &value) {
                if constexpr (std::is_base_of<label_property, Tag>::value) {
                    get<Tag>().update(x, y, label);
                }
                else {
                    get<Tag>().update(x, y, label, value);
                }

                if constexpr(sizeof...(SubTags) > 0) {
                    update<SubTags...>(x, y, label, value);
                }
            }
        };

        using label_type = CLabel;
        using image_type = CImage;
        using map_type = std::unordered_map<label_type, properties>;

        explicit object_properties(const image<CImage> &t_img, const image<CLabel> &t_label) {

            toolbox::assert_same_size(t_img, t_label);

            for(int y = 0; y < t_img.get_height(); ++y) {
                const CImage *row_img = t_img.row_ptr(y);
                const CLabel *row_label = t_label.row_ptr(y);
                for(int x = 0; x < t_img.get_width(); ++x) {
                    properties &prop = m_properties[row_label[x]];
                    prop.template update<PropertyTags...>(x, y, row_label[x], row_img[x]);
                }
            }
        }

        const map_type &data() const {
            return m_properties;
        };

        const properties &at(label_type t_label) const {
            return m_properties.at(t_label);
        }

        properties &at(label_type t_label) {
            return m_properties.at(t_label);
        }

        auto begin() {
            return m_properties.begin();
        }

        auto end() {
            return m_properties.end();
        }

        auto begin() const {
            return m_properties.begin();
        }

        auto end() const {
            return m_properties.end();
        }

    private:

        map_type m_properties;
    };


}