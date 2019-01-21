//
// Created by rgerst on 21.11.18.
//


#pragma once
#include <unordered_map>
#include <vector>

namespace coixx {
    /**
    * Interface for a histogram
    * @tparam C
    */
    template<class C> struct histogram {

        /**
         * Returns the count of a color
         * @param color
         * @return
         */
        virtual int get_count(const C &color) const = 0;

        /**
         * Returns the sum of counts
         * @return
         */
        virtual int get_sum() const = 0;

        /**
         * Returns the minimum key
         * @return
         */
        virtual C get_min_key() const = 0;

        /**
         * Returns the maximum key
         * @return
         */
        virtual C get_max_key() const = 0;

        /**
         * Returns true if the histogram is empty
         * @return
         */
        virtual bool empty() const = 0;

        /**
         * Gets the list of all keys
         * @return
         */
        virtual std::vector<C> get_keys() const = 0;
    };

    template<class C> struct mutable_histogram : public histogram<C> {
        /**
          * Counts a color
          * @param color
          * @param n
          */
        virtual void count(const C&color, int n) = 0;

        /**
         * Counts a color
         * @param color
         */
        void count(const C&color) {
            this->count(color, 1);
        }
    };

    /**
     * Histogram based on a
     * @tparam C
     */
    template<class C> struct hashmap_histogram : public mutable_histogram<C> {
        /**
         * Counts a color in the histogram
         * @param color
         * @param n
         */
        void count(const C&color, int n) override {
            m_data[color] += n;
            m_sum += n;
            if(color < m_min_key)
                m_min_key = color;
            if(color > m_max_key)
                m_max_key = color;
        }

        int get_count(const C &color) const override {
            auto it = m_data.find(color);
            if(it != m_data.end())
                return it->second;
            else
                return 0;
        }

        int get_sum() const override {
            return m_sum;
        }

        C get_min_key() const override {
            return m_min_key;
        }

        C get_max_key() const override {
            return m_max_key;
        }

        bool empty() const override {
            return m_data.empty();
        }

        std::vector<C> get_keys() const override {
            std::vector<C> result;
            result.reserve(m_data.size());
            for(const auto &kv : m_data) {
                result.push_back(kv.first);
            }
            return result;
        }

    private:
        std::unordered_map<C, int> m_data;
        int m_sum = 0;
        C m_min_key = C::last_value;
        C m_max_key = C::first_value;
    };
}