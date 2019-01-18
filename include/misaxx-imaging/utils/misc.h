//
// Created by rgerst on 18.01.19.
//


#pragma once

namespace misaxx_imaging::utils {

    /**
     * Cantor pairing function that transforms two natural numbers into a unique numerical representation of those numbers.
     * @tparam T
     * @param x
     * @param y
     * @return
     */
    template<class T> T cantor_pairing(T x, T y) {
        return static_cast<T>(y + 0.5 * (x + y) * (x + y + 1));
    }

}