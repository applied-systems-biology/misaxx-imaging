//
// Created by rgerst on 26.07.18.
//


#pragma once

#include <misaxx-imaging/coixx/toolbox/toolbox_traits.h>

/**
 * Contains some additional asserts.
 */
namespace coixx::toolbox {

    /**
   * Throws an exception if the images don't have the same size
   * @tparam I1
   * @tparam I2
   * @param i1
   * @param i2
   * @return
   */
    template<class I1, class I2> inline void assert_same_size(const I1 &i1, const I2 &i2) {
        if(i1.get_size() != i2.get_size())
            throw std::runtime_error("Images do not have the same size!");
    }

}