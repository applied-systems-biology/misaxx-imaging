//
// Created by rgerst on 28.05.18.
//


#pragma once

#include <misaxx/imaging/coixx/toolbox/toolbox_binarize.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_values.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_normalize.h>
#include <misaxx/imaging/coixx/toolbox/toolbox_morph.h>
#include <misaxx/imaging/coixx/structuring_element.h>
#include <misaxx/imaging/coixx/converters/semantic_convert.h>

namespace coixx::toolbox::binarize::superpixel {

    /**
     * Collects the edge information of each superpixel
     * @param t_superpixel_labels
     * @param t_gradient
     * @param t_neighbor_edges
     * @param t_neighboring_perimeter
     * @param t_neighboring_edginess
     */
    inline void collect_edge_information(const images::grayscale32s &t_superpixel_labels,
                                       const images::grayscale_float &t_gradient,
                                       images::mask &t_neighbor_edges,
                                       images::grayscale_double &t_neighboring_perimeter,
                                       images::grayscale_double &t_neighboring_edginess) {
        for(int y = 1; y < t_superpixel_labels.get_size().height - 1; ++y) {

            const auto *row_prev = t_superpixel_labels.row_ptr(y - 1);
            const auto *row = t_superpixel_labels.row_ptr(y);
            const auto *row_next = t_superpixel_labels.row_ptr(y + 1);
            const auto *row_edge = t_gradient.row_ptr(y);

            for(int x = 1; x < t_superpixel_labels.get_size().width - 1; ++x) {
                const int current = row[x];
                const int n = row_prev[x];
                const int s = row_next[x];
                const int e = row[x + 1];
                const int w = row[x - 1];

                if(n != current) {
                    t_neighbor_edges.get_image().at<uchar>(current, n) = 255;
                    t_neighboring_perimeter.get_image().at<double>(current, n) += 1;
                    t_neighboring_edginess.get_image().at<double>(current, n) += row_edge[x];
                }
                if(s != current) {
                    t_neighbor_edges.get_image().at<uchar>(current, s) = 255;
                    t_neighboring_perimeter.get_image().at<double>(current, s) += 1;
                    t_neighboring_edginess.get_image().at<double>(current, s) += row_edge[x];
                }
                if(e != current) {
                    t_neighbor_edges.get_image().at<uchar>(current, e) = 255;
                    t_neighboring_perimeter.get_image().at<double>(current, e) += 1;
                    t_neighboring_edginess.get_image().at<double>(current, e) += row_edge[x];
                }
                if(w != current) {
                    t_neighbor_edges.get_image().at<uchar>(current, w) = 255;
                    t_neighboring_perimeter.get_image().at<double>(current, w) += 1;
                    t_neighboring_edginess.get_image().at<double>(current, w) += row_edge[x];
                }
            }
        }
    }


//    /**
//     * Binarizes by finding the object that has highest boundary support & has high spatial coherence
//     *
//     * In contrast to the publication we use the image gradient and don't binarize the gradients.
//     * Instead, we use a canny filter with 0-threshold to find the reference pixels within the gradient image.
//     * Those reference pixels are dilated to ensure matching with superpixel borders.
//     * The the gradient value is used as "edginess" value.
//     *
//     * Yang, Michael Ying, and Bodo Rosenhahn.
//     * "Superpixel cut for figure-ground image segmentation."
//     * ISPRS Annals of the Photogrammetry, Remote Sensing and Spatial Information Sciences 3 (2016): 387.
//     *
//     * @tparam C
//     * @param t_img
//     * @param t_superpixel_labels
//     * @param t_superpixel_maxlabel
//     * @return
//     */
//    template<class C> inline images::mask by_canny_guided_contour(const image<C> &t_img,
//                                                                  const images::grayscale32s &t_superpixel_labels,
//                                                                  const int t_superpixel_maxlabel,
//                                                                  const double t_foreground_threshold = 0.5) {
//
//        static_assert(C::get_num_channels() == 1, "Must be a grayscale image");
//        using graph_type = typename misaxx::utils::math::max_flow::Graph<double, double, double>;
//
//        using namespace coixx::toolbox;
//
//        /**
//         * Build gradient image.
//         */
//        images::grayscale_float img_gradient = converters::semantic_convert<images::grayscale_float >(t_img)
//                << edge::sobel_gradient()
//                << normalize::by_max();
//
//        images::mask img_canny = converters::semantic_convert<images::mask>(t_img) << edge::canny(0, 0);
//
//        img_gradient << values::set_where_not(colors::grayscale_float::black(), img_canny) << morph::dilate(structuring_element::circle(3));
//
//        /*
//         * Analyze the borders between superpixels + area
//         */
//        images::mask neighbor_edges(cv::Size(t_superpixel_maxlabel + 1, t_superpixel_maxlabel + 1), colors::mask::background());
//        images::grayscale_double neighboring_perimeter(cv::Size(t_superpixel_maxlabel + 1, t_superpixel_maxlabel + 1), colors::grayscale_double::black());
//        images::grayscale_double neighboring_edginess(cv::Size(t_superpixel_maxlabel + 1, t_superpixel_maxlabel + 1), colors::grayscale_double::black());
//
//        collect_edge_information(t_superpixel_labels, img_gradient, neighbor_edges, neighboring_perimeter, neighboring_edginess);
//
//        /*
//         * Build graph where each node represents a superpixel.
//         * Each node has edge to source and to sink.
//         */
//        graph_type graph(t_superpixel_maxlabel + 1, statistics::count_non_zero(neighbor_edges));
//        graph.add_node(t_superpixel_maxlabel + 1);
//
//        // Add Source/sink edges
//        // Otsu-covered pixels are set as SOURCE
//        // Non-Otsu-covered border pixels are set as SINK
//        // Other superpixels are left alone
//
//        images::mask img_otsu = converters::semantic_convert<images::mask>(t_img) << binarize::otsu();
//
//        labeled_image_properties<C> superpixel_properties(t_img, t_superpixel_labels);
//        labeled_image_properties<colors::mask> superpixel_otsu_properties(img_otsu, t_superpixel_labels);
//
//        for(const auto &kv : superpixel_otsu_properties.get_properties()) {
//            if(kv.second.get_average_value() / 255.0 >= t_foreground_threshold) {
//                graph.add_tweights(kv.first, 1000000, 0);
//            }
//            else if(kv.second.is_border) {
//                graph.add_tweights(kv.first, 0, 1000000);
//            }
//        }
//
//        // Add neighbor edges
//        for(int label = 0; label <= t_superpixel_maxlabel; ++label) {
//            const auto *row = toolbox2::const_row(neighbor_edges, label);
//
//            for(int other_label = label + 1; other_label <= t_superpixel_maxlabel; ++other_label) {
//                const bool is_connected = row[other_label] > 0;
//
//                if(is_connected) {
//
//                    const double perimeter = neighboring_perimeter.get_image().at<double>(label, other_label);
//                    const double edginess = neighboring_edginess.get_image().at<double>(label, other_label);
//
//                    double bg = perimeter - edginess;
//                    graph.add_edge(label, other_label, bg, bg);
//                }
//            }
//        }
//
//        /**
//         * Calculate the max flow that will be used as cut-off to segment background from foreground.
//         * Use recoloring to segment the graph
//         */
//        graph.maxflow();
//
//        recoloring_any_to_any<colors::grayscale32s, colors::mask> lut;
//        lut.reserve(static_cast<size_t>(t_superpixel_maxlabel) + 1);
//
//        for(int label = 0; label <= t_superpixel_maxlabel; ++label) {
//            if(graph.what_segment(label) == graph_type::SOURCE) {
//                lut.recolor(label, 255);
//            }
//            else {
//                lut.recolor(label, 0);
//            }
////            if(superpixel_otsu_properties.get_properties().at(label).get_average_value() >= 128)
////                lut.recolor(label, 128);
//        }
//
//        images::mask result(t_superpixel_labels.get_size(), colors::mask::background());
//        lut.apply(t_superpixel_labels, result);
////        result.show("superpixel labels");
//
////        images::grayscale32s lapl_labels = t_superpixel_labels.clone();
////        image_filter2::edge::laplacian(lapl_labels);
//
////        image_filter2::visualization::mask(result, t_img).show("final graph segmentation mask");
////        image_filter2::visualization::mask(result, img_gradient).show("final graph segmentation mask on gradient");
////        image_filter2::visualization::mask(toolbox2::to_mask(lapl_labels), img_gradient).show_and_wait("superpixel borders on gradient");
//
//        return result;
//    }

//    /**
//     * Binarizes by average intensity.
//     *
//     * Simayijiang, Zhayida, and Stefanie Grimm.
//     * "Segmentation with Graph Cuts." Matematikcentrum Lunds Universitet.[Online].
//     * Available: http://www. maths. lth. se/matematiklth/personal/petter/rappo rter/graph. pdf.[Diakses 8 Mei 2017].
//     * @tparam C
//     * @param t_img
//     * @param t_superpixel_labels
//     * @param t_superpixel_maxlabel Maximum label of superpixel_labels
//     * @param t_mu_foreground Mean intensity of the foreground object
//     * @param t_mu_background Mean intensity of the background object
//     * @param t_lambda Low lambda emphasises data term, high lambda emphasizes object boundary length
//     * @return
//     */
//    template<class C> inline images::mask by_average_intensity(const image<C> &t_img,
//                                                              const images::grayscale32s &t_superpixel_labels,
//                                                              const int t_superpixel_maxlabel,
//                                                              const double t_mu_foreground,
//                                                              const double t_mu_background,
//                                                              const double t_lambda) {
//        static_assert(C::get_num_channels() == 1, "Must be a grayscale image");
//        using graph_type = typename misaxx::utils::math::max_flow::Graph<double, double, double>;
//
//        /**
//         * Find the neighbor edges of the superpixels
//         */
//        images::mask neighbor_edges(cv::Size(t_superpixel_maxlabel + 1, t_superpixel_maxlabel + 1), colors::mask::background());
//
//        for(int y = 1; y < t_superpixel_labels.get_size().height - 1; ++y) {
//
//            const auto *row_prev = toolbox2::const_row(t_superpixel_labels, y - 1);
//            const auto *row = toolbox2::const_row(t_superpixel_labels, y);
//            const auto *row_next = toolbox2::const_row(t_superpixel_labels, y + 1);
//
//            for(int x = 1; x < t_superpixel_labels.get_size().width - 1; ++x) {
//                const int current = row[x];
//                const int n = row_prev[x];
//                const int s = row_next[x];
//                const int e = row[x + 1];
//                const int w = row[x - 1];
//
//                if(n != current)
//                    neighbor_edges.get_image().at<uchar>(current, n) = 255;
//                if(s != current)
//                    neighbor_edges.get_image().at<uchar>(current, s) = 255;
//                if(e != current)
//                    neighbor_edges.get_image().at<uchar>(current, e) = 255;
//                if(w != current)
//                    neighbor_edges.get_image().at<uchar>(current, w) = 255;
//            }
//        }
//
////        neighbor_edges.show_and_wait("neighbor edges");
//
//        /*
//         * Build graph where each node represents a superpixel.
//         * Each node has edge to source and to sink.
//         * Cost of source edge is (avg(pixel) - mu_1)^2.
//         * Cost of sink edge is (avg(pixel) - mu_2)^2
//         * Cost between pixel neighbors is lambda.
//         */
//        graph_type graph(t_superpixel_maxlabel + 1, toolbox2::count_non_zero(neighbor_edges));
//        graph.add_node(t_superpixel_maxlabel + 1);
//
//        // Add Source/sink edges
//        labeled_image_properties<C> properties(t_img, t_superpixel_labels);
//        for(const auto &kv : properties.get_properties()) {
//            double source_weight = std::pow(kv.second.get_average_value() - t_mu_foreground, 2.0);
//            double sink_weight = std::pow(kv.second.get_average_value() - t_mu_background, 2.0);
//            graph.add_tweights(kv.first, source_weight, sink_weight);
//        }
//
//        // Add neighbor edges
//
//        for(int label = 0; label <= t_superpixel_maxlabel; ++label) {
//            const auto *row = toolbox2::const_row(neighbor_edges, label);
//
//            for(int other_label = 0; other_label <= t_superpixel_maxlabel; ++other_label) {
//
//                if(label == other_label)
//                    continue;
//
//                const bool is_connected = row[other_label] > 0;
//
//                if(is_connected)
//                    graph.add_edge(label, other_label, t_lambda, t_lambda);
//            }
//        }
//
//        /**
//         * Calculate the max flow that will be used as cut-off to segment background from foreground.
//         * Use recoloring to segment the graph
//         */
//         graph.maxflow();
//
//         recoloring_any_to_any<colors::grayscale32s, colors::mask> lut;
//         lut.reserve(static_cast<size_t>(t_superpixel_maxlabel) + 1);
//
//         for(int label = 0; label <= t_superpixel_maxlabel; ++label) {
//             if(graph.what_segment(label, graph_type::SOURCE)) {
//                 lut.recolor(label, 255);
//             }
//             else {
//                 lut.recolor(label, 0);
//             }
//         }
//
//         images::mask result(t_superpixel_labels.get_size(), colors::mask::background());
//         lut.apply(t_superpixel_labels, result);
//
////         image_filter2::visualization::mask(result, t_img).show_and_wait("final graph segmentation mask");
//
//         return result;
//    }
}
