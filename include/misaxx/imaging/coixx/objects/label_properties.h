//
// Created by rgerst on 23.07.18.
//


#pragma once

#include <misaxx/imaging/coixx/image.h>

namespace coixx {

    /**
     * Base class for all label properties.
     * Must be inside of a struct that contains the actual type.
     *
     * Template for custom label_properties:
     * struct my_property {
     *  template<class C, Void = void> struct type : public label_property {
     *      inline void update(int x, int y, typename C::raw_type value);
     *  }
     * }
     */
    struct label_property {

    };

    /**
     * Calculates properties for each object.
     * @tparam C Color space of the input image
     * @tparam MapTag misaxx::utils::math::function map tag (e.g. misaxx::utils::math::function::map_hashmap) that indicates which map should be used
     * @tparam PropertyTags Any set of tag structs that contain a sub-type "type" based on object_property_t
     */
    template<class C = colors::grayscale32s, class ... PropertyTags> struct label_properties {

        struct properties : public PropertyTags::template type<C>... {

            template<class Tag, class Type = typename Tag::template type<C>> Type &get() {
                return *this;
            }

            template<class Tag, class Type = typename Tag::template type<C>> const Type &get() const {
                return *this;
            }

            template<class Tag, class ... SubTags> void update(int x, int y, const C &value) {
                get<Tag>().update(x, y, value);
                if constexpr(sizeof...(SubTags) > 0) {
                    update<SubTags...>(x, y, value);
                }
            }
        };

        using map_type = std::unordered_map<C, properties>;

        explicit label_properties(const image<C> &t_img) {
            for(int y = 0; y < t_img.get_height(); ++y) {
                const C* row = t_img.row_ptr(y);
                for(int x = 0; x < t_img.get_width(); ++x) {
                    properties &prop = m_properties[row[x]];
                    prop.template update<PropertyTags...>(x, y, row[x]);
                }
            }
        }

        const map_type &data() const {
            return m_properties;
        };

        const properties &at(const C &t_label) const {
            return m_properties.at(t_label);
        }

        properties &at(const C &t_label) {
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