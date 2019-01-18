cmake_minimum_required(VERSION 3.11)
project(misaxx-imaging-core VERSION 0.1.0 DESCRIPTION "MISA++ Imaging Core")

find_package(misaxx-core REQUIRED)
find_package(OpenCV 4 COMPONENTS REQUIRED core imgproc ximgproc imgcodecs highgui)
find_package(TIFF REQUIRED)

add_library(misaxx-imaging
        include/misaxx-imaging/accessors/misa_image_file.h
        include/misaxx-imaging/accessors/misa_image_stack.h
        include/misaxx-imaging/caches/misa_image_file_cache.h
        include/misaxx-imaging/caches/misa_image_stack_cache.h
        include/misaxx-imaging/patterns/misa_image_file_pattern.h
        include/misaxx-imaging/patterns/misa_image_file_stack_pattern.h
        src/misaxx-imaging/accessors/misa_image_file.cpp
        src/misaxx-imaging/accessors/misa_image_stack.cpp
        src/misaxx-imaging/caches/misa_image_file_cache.cpp
        src/misaxx-imaging/caches/misa_image_stack_cache.cpp
        src/misaxx-imaging/patterns/misa_image_file_pattern.cpp
        src/misaxx-imaging/patterns/misa_image_file_stack_pattern.cpp
        include/misaxx-imaging/coixx/margin.h
        include/misaxx-imaging/coixx/pixel_value.h
        include/misaxx-imaging/coixx/colors/color_bgr_uint8.h
        include/misaxx-imaging/coixx/colors/color_hsv_uint8.h
        include/misaxx-imaging/coixx/structuring_element.h
        include/misaxx-imaging/coixx/pixel.h
        include/misaxx-imaging/coixx/io/image_io.h
        include/misaxx-imaging/coixx/toolbox/toolbox_generate.h
        include/misaxx-imaging/coixx/objects/contour.h
        include/misaxx-imaging/coixx/toolbox/toolbox_binarize_superpixel_graphcut.h
        include/misaxx-imaging/coixx/image.h
        include/misaxx-imaging/coixx/toolbox/toolbox_blur.h
        include/misaxx-imaging/coixx/toolbox/toolbox.h
        include/misaxx-imaging/coixx/toolbox/toolbox_binarize.h
        include/misaxx-imaging/coixx/toolbox/toolbox_binarize_componentotsu.h
        include/misaxx-imaging/coixx/toolbox/toolbox_binarize_huang.h
        include/misaxx-imaging/coixx/toolbox/toolbox_normalize.h
        include/misaxx-imaging/coixx/toolbox/toolbox_morph.h
        include/misaxx-imaging/coixx/toolbox/toolbox_labeling.h
        include/misaxx-imaging/coixx/toolbox/toolbox_bitwise.h
        include/misaxx-imaging/coixx/toolbox/toolbox_operators.h
        include/misaxx-imaging/coixx/toolbox/toolbox_values.h
        include/misaxx-imaging/coixx/toolbox/toolbox_distance_transform.h
        include/misaxx-imaging/coixx/toolbox/toolbox_objects.h
        include/misaxx-imaging/coixx/toolbox/toolbox_utils.h
        include/misaxx-imaging/coixx/toolbox/toolbox_compose.h
        include/misaxx-imaging/coixx/toolbox/toolbox_mask.h
        include/misaxx-imaging/coixx/toolbox/toolbox_visualization.h
        include/misaxx-imaging/coixx/visualizer_gui.h
        include/misaxx-imaging/coixx/toolbox/toolbox_localminmax.h
        include/misaxx-imaging/coixx/toolbox/toolbox_edge.h
        include/misaxx-imaging/coixx/toolbox/toolbox_visualize_graph_flow.h
        include/misaxx-imaging/coixx/toolbox/toolbox_blob.h
        include/misaxx-imaging/coixx/toolbox/toolbox_morph_cross.h
        include/misaxx-imaging/coixx/toolbox/toolbox_generic.h
        include/misaxx-imaging/coixx/io/tiff_reader.h
        include/misaxx-imaging/coixx/io/tiff_writer.h
        include/misaxx-imaging/coixx/toolbox/toolbox_text.h
        include/misaxx-imaging/coixx/toolbox/toolbox_recoloring.h
        include/misaxx-imaging/coixx/toolbox/toolbox_resize.h
        include/misaxx-imaging/coixx/toolbox/toolbox_statistics.h
        include/misaxx-imaging/coixx/objects/label_properties.h
        include/misaxx-imaging/coixx/objects/object_properties.h
        include/misaxx-imaging/coixx/toolbox/toolbox_io.h
        include/misaxx-imaging/coixx/converters/semantic_convert.h
        include/misaxx-imaging/coixx/converters/hard_convert.h
        include/misaxx-imaging/coixx/io/auto_image_io.h
        include/misaxx-imaging/coixx/algorithms/superpixels_slic.h
        include/misaxx-imaging/coixx/objects/label_min_max_position.h
        include/misaxx-imaging/coixx/objects/label_centroid_position.h
        include/misaxx-imaging/coixx/objects/label_pixel_count.h
        include/misaxx-imaging/coixx/objects/object_pixel_stats.h
        include/misaxx-imaging/coixx/objects/object_histogram.h
        include/misaxx-imaging/coixx/toolbox/toolbox_traits.h
        include/misaxx-imaging/coixx/toolbox/toolbox_assert.h
        include/misaxx-imaging/coixx/converters/reinterpret_convert.h
        include/misaxx-imaging/coixx/objects/object_average_intensity.h
        include/misaxx-imaging/coixx/colors/color_grayscale_int.h
        include/misaxx-imaging/coixx/colors/color_grayscale_floating.h
        include/misaxx-imaging/coixx/histogram.h
        include/misaxx-imaging/coixx/recoloring_map.h
        include/misaxx-imaging/coixx/thresholding.h
        include/misaxx-imaging/coixx/cumulative_histogram.h
        include/misaxx-imaging/coixx/toolbox/toolbox_channels.h
        include/misaxx-imaging/coixx/toolbox/toolbox_opencv.h
        src/misaxx-imaging/coixx/io/tiff_reader.cpp
        src/misaxx-imaging/coixx/io/tiff_writer.cpp
        include/misaxx-imaging/coixx/objects/label_dummy_property.h
        src/misaxx-imaging/coixx/colors/color_bgr_uint8.cpp
        src/misaxx-imaging/coixx/colors/color_hsv_uint8.cpp
        include/misaxx-imaging/coixx/algorithms/superpixels_slic_algorithm.h
        src/misaxx-imaging/coixx/algorithms/superpixels_slic.cpp
        src/misaxx-imaging/coixx/objects/contour.cpp
        src/misaxx-imaging/coixx/margin.cpp
        src/misaxx-imaging/coixx/structuring_element.cpp
        src/misaxx-imaging/coixx/visualizer_gui.cpp include/misaxx-imaging/utils/percentiles.h)

misaxx_make_shared(misaxx misaxx-imaging)
misaxx_add_compiler_warnings(misaxx-imaging)

target_include_directories(misaxx-imaging PUBLIC $<BUILD_INTERFACE:${OpenCV_INCLUDE_DIR}>)
target_include_directories(misaxx-imaging PUBLIC $<BUILD_INTERFACE:${TIFF_INCLUDE_DIR}>)
target_link_libraries(misaxx-imaging PUBLIC ${OpenCV_LIBS}
        ${TIFF_LIBRARIES}
        misaxx::misaxx-core)
