//
// Created by rgerst on 28.01.19.
//

#include <misaxx/imaging/utils/cv2/toolbox/toolbox_morph.h>
#include <stack>

#include "misaxx/imaging/utils/cv2/toolbox/toolbox_morph.h"

void cv::toolbox::morph::dilate(cv::images::grayscale8u &img, const cv::images::mask &kernel, int iterations) {
    cv::dilate(img, img.buffer(true), kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::erode(cv::images::grayscale8u &img, const cv::images::mask &kernel, int iterations) {
    cv::erode(img, img.buffer(true), kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::open(cv::images::grayscale8u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_OPEN, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::close(cv::images::grayscale8u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::gradient(cv::images::grayscale8u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_GRADIENT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::tophat(cv::images::grayscale8u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_TOPHAT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::blackhat(cv::images::grayscale8u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_BLACKHAT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::hitmiss(cv::images::grayscale8u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_HITMISS, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::dilate(cv::images::grayscale16u &img, const cv::images::mask &kernel, int iterations) {
    cv::dilate(img, img.buffer(true), kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::erode(cv::images::grayscale16u &img, const cv::images::mask &kernel, int iterations) {
    cv::erode(img, img.buffer(true), kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::open(cv::images::grayscale16u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_OPEN, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::close(cv::images::grayscale16u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::gradient(cv::images::grayscale16u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_GRADIENT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::tophat(cv::images::grayscale16u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_TOPHAT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::blackhat(cv::images::grayscale16u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_BLACKHAT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::hitmiss(cv::images::grayscale16u &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_HITMISS, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::dilate(cv::images::grayscale16s &img, const cv::images::mask &kernel, int iterations) {
    cv::dilate(img, img.buffer(true), kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::erode(cv::images::grayscale16s &img, const cv::images::mask &kernel, int iterations) {
    cv::erode(img, img.buffer(true), kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::open(cv::images::grayscale16s &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_OPEN, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::close(cv::images::grayscale16s &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::gradient(cv::images::grayscale16s &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_GRADIENT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::tophat(cv::images::grayscale16s &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_TOPHAT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::blackhat(cv::images::grayscale16s &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_BLACKHAT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::hitmiss(cv::images::grayscale16s &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_HITMISS, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::dilate(cv::images::grayscale32f &img, const cv::images::mask &kernel, int iterations) {
    cv::dilate(img, img.buffer(true), kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::erode(cv::images::grayscale32f &img, const cv::images::mask &kernel, int iterations) {
    cv::erode(img, img.buffer(true), kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::open(cv::images::grayscale32f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_OPEN, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::close(cv::images::grayscale32f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::gradient(cv::images::grayscale32f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_GRADIENT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::tophat(cv::images::grayscale32f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_TOPHAT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::blackhat(cv::images::grayscale32f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_BLACKHAT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::hitmiss(cv::images::grayscale32f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_HITMISS, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::dilate(cv::images::grayscale64f &img, const cv::images::mask &kernel, int iterations) {
    cv::dilate(img, img.buffer(true), kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::erode(cv::images::grayscale64f &img, const cv::images::mask &kernel, int iterations) {
    cv::erode(img, img.buffer(true), kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::open(cv::images::grayscale64f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_OPEN, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::close(cv::images::grayscale64f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::gradient(cv::images::grayscale64f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_GRADIENT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::tophat(cv::images::grayscale64f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_TOPHAT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::blackhat(cv::images::grayscale64f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_BLACKHAT, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

void cv::toolbox::morph::hitmiss(cv::images::grayscale64f &img, const cv::images::mask &kernel, int iterations) {
    cv::morphologyEx(img, img.buffer(true), cv::MORPH_HITMISS, kernel, cv::Point(-1, -1), iterations);
    img.swap();
}

namespace {
    template<typename T> void close_holes_impl(cv::images::grayscale &img, const cv::images::mask &kernel, T black, T white) {

        cv::Mat &img_buf = img.buffer(true);
        img_buf = black; // Set to "0"

        std::vector<cv::Point> neighbors;
        std::stack<cv::Point> stack;

        for(int i = 0; i < kernel.rows; ++i) {
            const auto *row = kernel.static_ptr(i);
            for(int j = 0; j < kernel.cols; ++j) {
                if(row[j] > 0) {
                    neighbors.emplace_back(cv::Point(j - kernel.cols / 2, i - kernel.rows / 2));
                }
            }
        }

        // Find the points in x direction (1st dimension)
        cv::Point pos(0,0);

        int rows = img.rows;
        int cols = img.cols;

        for(int i = 0; i < rows; ++i) {
            pos.x = 0;

            if(img.at<T>(pos) == 0 && img_buf.at<T>(pos) == 0) {
                img_buf.at<T>(pos) = white;
                stack.push(pos);
            }

            pos.x = cols - 1;

            if(img.at<T>(pos) == 0 && img_buf.at<T>(pos) == 0) {
                img_buf.at<T>(pos) = white;
                stack.push(pos);
            }

            // Increase counter of y
            if(pos.y < rows) {
                ++pos.y;
            }
            else {
                pos.y = 0;
            }
        }

        pos = cv::Point(0,0);

        // Find the points in y direction (2nd dimension)

        for(int i = 0; i < cols; ++i) {
            pos.y = 0;

            if(img.at<T>(pos) == 0 && img_buf.at<T>(pos) == 0) {
                img_buf.at<T>(pos) = white;
                stack.push(pos);
            }

            pos.y = rows - 1;

            if(img.at<T>(pos) == 0 && img_buf.at<T>(pos) == 0) {
                img_buf.at<T>(pos) = white;
                stack.push(pos);
            }

            // Increase counter of y
            if(pos.x < cols) {
                ++pos.x;
            }
            else {
                pos.x = 0;
            }
        }

        // Apply
        while(!stack.empty()) {
            cv::Point pos2 = stack.top();
            stack.pop();

            for(const cv::Point & rel_neighbor : neighbors) {
                cv::Point absolute = rel_neighbor + pos2;

                if(absolute.x >= 0 && absolute.y >= 0 && absolute.x < img.cols && absolute.y < img.rows) {
                    if(img.at<T>(absolute) == 0 && img_buf.at<T>(absolute) == 0) {
                        img_buf.at<T>(absolute) = white;
                        stack.push(absolute);
                    }
                }
            }
        }

        // Invert the image
        for(int i = 0; i < img_buf.rows; ++i) {
            auto *row = img_buf.ptr<T>(i);
            for(int j = 0; j < img_buf.cols; ++j) {
                row[j] = white - row[j];
            }
        }

        img.swap();
    }
}

void cv::toolbox::morph::close_holes(cv::images::grayscale8u &img, const cv::images::mask &kernel) {
    close_holes_impl<ushort>(img, kernel, 0, std::numeric_limits<uchar>::max());
}

void cv::toolbox::morph::close_holes(cv::images::grayscale16u &img, const cv::images::mask &kernel) {
    close_holes_impl<ushort>(img, kernel, 0, std::numeric_limits<ushort>::max());
}

void cv::toolbox::morph::close_holes(cv::images::grayscale32f &img, const cv::images::mask &kernel) {
    close_holes_impl<float>(img, kernel, 0, 1);
}

void cv::toolbox::morph::close_holes(cv::images::grayscale64f &img, const cv::images::mask &kernel) {
    close_holes_impl<double>(img, kernel, 0, 1);
}
