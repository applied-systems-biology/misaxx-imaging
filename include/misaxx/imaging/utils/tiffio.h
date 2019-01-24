//
// Created by rgerst on 24.01.19.
//

#pragma once

#include <opencv2/opencv.hpp>
#include <boost/filesystem/path.hpp>

namespace misaxx::imaging::utils {
    /**
     * Reads a cv::Mat from TIFF. Supports all types supported by OpenCV
     * @param t_path
     * @return
     */
    extern cv::Mat tiffread(const boost::filesystem::path &t_path);

    /**
     * Writes a cv::Mat to TIFF. Supports all types supported by OpenCV
     * @param t_img
     * @param t_path
     */
    extern void tiffwrite(const cv::Mat &t_img, const boost::filesystem::path &t_path);
}




