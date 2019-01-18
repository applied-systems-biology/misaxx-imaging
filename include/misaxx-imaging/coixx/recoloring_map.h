//
// Created by rgerst on 21.11.18.
//


#pragma once

#include <stdexcept>
#include <unordered_map>

namespace coixx {
    /**
     * Interface for all recoloring functions
     * @tparam Csrc
     * @tparam Cdst
     */
    template<class Csrc, class Cdst = Csrc>
    struct recoloring_map {
        virtual Cdst recolor(const Csrc &key) const = 0;
    };

    template<class Csrc, class Cdst = Csrc>
    struct mutable_recoloring_map : public recoloring_map<Csrc, Cdst> {
        virtual void set_recolor(const Csrc &key, const Cdst &value) = 0;
    };

    /**
     * Identity recoloring map. Csrc and Cdst must be same
     * @tparam Csrc
     * @tparam Cdst
     */
    template<class C>
    struct identity_recoloring : public recoloring_map<C, C> {
        C recolor(const C &key) const override {
            return key;
        }
    };

    /**
     * Recoloring that always recolors to Cdst::default_value (which is usually zero)
     * @tparam Csrc
     * @tparam Cdst
     */
    template<class Csrc, class Cdst = Csrc>
    struct zero_recoloring : public recoloring_map<Csrc, Cdst> {
        Cdst recolor(const Csrc &key) const override {
            return Cdst::default_value;
        }
    };

    /**
     * Recoloring that always throws an exception
     * @tparam Csrc
     * @tparam Cdst
     */
    template<class Csrc, class Cdst = Csrc>
    struct invalid_recoloring : public recoloring_map<Csrc, Cdst> {
        Cdst recolor(const Csrc &) const override {
            throw std::runtime_error("Invalid recoloring!");
        }
    };

    /**
     * Recoloring map based on an unordered_map
     * @tparam Csrc
     * @tparam Cdst
     * @tparam FDefault
     */
    template<class Csrc, class Cdst = Csrc, class FDefault = invalid_recoloring<Csrc, Cdst>>
    struct recoloring_hashmap : public mutable_recoloring_map<Csrc, Cdst> {
        std::unordered_map<Csrc, Cdst> data;
        FDefault default_output;

        Cdst recolor(const Csrc &key) const override {
            auto it = data.find(key);
            if (it != data.end()) {
                return it->second;
            } else {
                return default_output.recolor(key);
            }
        }

        void set_recolor(const Csrc &key, const Cdst &value) override {
            data[key] = value;
        }
    };

    /**
     * Convenience type for a recoloring hashmap that default to an identity transformation
     */
    template<class C> using identity_recoloring_hashmap = recoloring_hashmap<C, C, identity_recoloring<C>>;

    /**
     * Convenience type for a recoloring hashmap that default to a zero transformation
     */
    template <class CSrc, class CDst = CSrc> using zero_recoloring_hashmap = recoloring_hashmap<CSrc, CDst, zero_recoloring<CSrc, CDst>>;
}