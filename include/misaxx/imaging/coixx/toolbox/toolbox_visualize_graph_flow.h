//
// Created by rgerst on 28.06.18.
//


#pragma once

#include <misaxx/imaging/coixx/image.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_values.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_normalize.h>

namespace coixx::toolbox::visualize {

    /**
     * Visualizes the inverted flow in the graph (high intensity = low flow)
     * @param t_superpixel_labels
     * @param t_neighboring_perimeter
     * @param t_neighboring_edginess
     * @return
     */
    inline images::grayscale_float visualize_graph_flow(const images::grayscale32s &t_superpixel_labels,
                                                        images::grayscale_double &t_neighboring_perimeter,
                                                        images::grayscale_double &t_neighboring_edginess) {
        images::grayscale_float flow_visualization(t_superpixel_labels.get_size(), colors::grayscale_float::white());

        for(int y = 1; y < t_superpixel_labels.get_size().height - 1; ++y) {

            const auto *row_prev = t_superpixel_labels.row_ptr(y - 1);
            const auto *row = t_superpixel_labels.row_ptr(y);
            const auto *row_next = t_superpixel_labels.row_ptr(y + 1);
            auto *row_vis = flow_visualization.row_ptr(y);

            for(int x = 1; x < t_superpixel_labels.get_size().width - 1; ++x) {
                const int current = row[x];
                const int n = row_prev[x];
                const int s = row_next[x];
                const int e = row[x + 1];
                const int w = row[x - 1];

                if(n != current) {
                    const double perimeter = t_neighboring_perimeter.get_image().at<double>(current, n);
                    const double edginess = t_neighboring_edginess.get_image().at<double>(current, n);
                    row_vis[x] = static_cast<float>(perimeter - edginess);
                }
                else if(s != current) {
                    const double perimeter = t_neighboring_perimeter.get_image().at<double>(current, s);
                    const double edginess = t_neighboring_edginess.get_image().at<double>(current, s);
                    row_vis[x] = static_cast<float>(perimeter - edginess);
                }
                else if(e != current) {
                    const double perimeter = t_neighboring_perimeter.get_image().at<double>(current, e);
                    const double edginess = t_neighboring_edginess.get_image().at<double>(current, e);
                    row_vis[x] = static_cast<float>(perimeter - edginess);
                }
                else if(w != current) {
                    const double perimeter = t_neighboring_perimeter.get_image().at<double>(current, w);
                    const double edginess = t_neighboring_edginess.get_image().at<double>(current, w);
                    row_vis[x] = static_cast<float>(perimeter - edginess);
                }
            }
        }

        using namespace coixx::toolbox;

        flow_visualization << values::invert() << normalize::by_max();

        return flow_visualization;
    }

}
