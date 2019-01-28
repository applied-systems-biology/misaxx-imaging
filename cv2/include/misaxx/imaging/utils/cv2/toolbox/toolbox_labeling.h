//
// Created by rgerst on 28.01.19.
//

#pragma once


#include <misaxx/imaging/utils/cv2/static_types.h>
#include <misaxx/imaging/utils/cv2/connectivity.h>


namespace cv::toolbox::labeling {

    images::labels connected_components(const images::mask &img, connectivity connectivity);

}



