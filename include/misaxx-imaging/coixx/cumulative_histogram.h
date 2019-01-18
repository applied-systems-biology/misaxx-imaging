//
// Created by rgerst on 21.11.18.
//


#pragma once

#include <memory>
#include "histogram.h"

namespace coixx {

    /**
     * Cumulative histogram that wraps around another histogram
     * @tparam C
     */
    template<class C> struct wrapping_cumulative_histogram : public histogram<C> {

        template<class H> explicit wrapping_cumulative_histogram(H hist) : m_base_histogram(std::make_unique<H>(std::move(hist))) {
        }

        int get_count(const C &color) const override {
            auto it = m_cache.find(color);
            if (it != m_cache.end())
                return it->second;
            else {
                int result = m_base_histogram->get_count(color);
                if(color != m_base_histogram->get_min_key()) {
                    result += get_count(color - C(1));
                }
                m_cache[color] = result;
                return result;
            }
        }

        int get_sum() const override {
            int result = 0;
            if(!m_base_histogram->empty()) {
                C current = m_base_histogram->get_min_key();
                do {
                    result += get_count(current);
                }
                while(current != m_base_histogram->get_max_key());
            }
            return result;
        }

        C get_min_key() const override {
            return m_base_histogram->get_min_key();
        }

        C get_max_key() const override {
            return m_base_histogram->get_max_key();
        }

        std::vector<C> get_keys() const override {
            return m_base_histogram->get_keys();
        }

        bool empty() const override {
            return m_base_histogram->empty();
        }

    private:
        std::unique_ptr<histogram<C>> m_base_histogram;
        mutable std::unordered_map<C, int> m_cache;
    };

    /**
     * Weighted cumulative histogram that wraps around another histogram
     * @tparam C
     */
    template<class C> struct wrapping_weighted_cumulative_histogram : public histogram<C> {

        template<class H> explicit wrapping_weighted_cumulative_histogram(H hist) : m_base_histogram(std::make_unique<H>(std::move(hist))) {
        }

        int get_count(const C &color) const override {
            auto it = m_cache.find(color);
            if (it != m_cache.end())
                return it->second;
            else {
                int result = m_base_histogram->get_count(color) * color;
                if(color != m_base_histogram->get_min_key()) {
                    result += get_count(color - C(1));
                }
                m_cache[color] = result;
                return result;
            }
        }

        int get_sum() const override {
            int result = 0;
            if(!m_base_histogram->empty()) {
                C current = m_base_histogram->get_min_key();
                do {
                    result += get_count(current);
                }
                while(current != m_base_histogram->get_max_key());
            }
            return result;
        }

        C get_min_key() const override {
            return m_base_histogram->get_min_key();
        }

        C get_max_key() const override {
            return m_base_histogram->get_max_key();
        }

        std::vector<C> get_keys() const override {
            return m_base_histogram->get_keys();
        }

        bool empty() const override {
            return m_base_histogram->empty();
        }

    private:
        std::unique_ptr<histogram<C>> m_base_histogram;
        mutable std::unordered_map<C, int> m_cache;
    };
}