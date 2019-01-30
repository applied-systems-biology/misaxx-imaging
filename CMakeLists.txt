cmake_minimum_required(VERSION 3.11)
project(misaxx-imaging VERSION 0.1.0 DESCRIPTION "MISA++ Imaging Core")

#set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(misaxx-core REQUIRED)
find_package(OpenCV 4 COMPONENTS REQUIRED core imgproc ximgproc imgcodecs highgui)
find_package(TIFF REQUIRED)

add_library(misaxx-imaging
        include/misaxx/imaging/accessors/misa_image_file.h
        include/misaxx/imaging/accessors/misa_image_stack.h
        include/misaxx/imaging/caches/misa_image_file_cache.h
        include/misaxx/imaging/caches/misa_image_stack_cache.h
        include/misaxx/imaging/patterns/misa_image_pattern.h
        include/misaxx/imaging/patterns/misa_image_stack_pattern.h
        src/misaxx/imaging/accessors/misa_image_file.cpp
        src/misaxx/imaging/accessors/misa_image_stack.cpp
        src/misaxx/imaging/caches/misa_image_file_cache.cpp
        src/misaxx/imaging/caches/misa_image_stack_cache.cpp
        src/misaxx/imaging/patterns/misa_image_pattern.cpp
        src/misaxx/imaging/patterns/misa_image_stack_pattern.cpp
        include/misaxx/imaging/utils/percentiles.h
        include/misaxx/imaging/utils/thresholding.h
        include/misaxx/imaging/utils/misc.h
        src/misaxx/imaging/descriptions/misa_image_description.cpp
        include/misaxx/imaging/descriptions/misa_image_description.h
        src/misaxx/imaging/descriptions/misa_image_stack_description.cpp
        include/misaxx/imaging/descriptions/misa_image_stack_description.h
        src/misaxx/imaging/utils/tiffio.cpp
        include/misaxx/imaging/utils/tiffio.h)

set(MISAXX_LIBRARY misaxx-imaging)
set(MISAXX_LIBRARY_NAMESPACE misaxx::)
set(MISAXX_API_NAME misaxx_imaging)
set(MISAXX_API_INCLUDE_PATH misaxx/imaging)
set(MISAXX_API_NAMESPACE misaxx::imaging)
misaxx_with_default_module_info()
misaxx_with_default_api()

target_include_directories(misaxx-imaging PUBLIC $<BUILD_INTERFACE:${OpenCV_INCLUDE_DIR}>)
target_include_directories(misaxx-imaging PUBLIC $<BUILD_INTERFACE:${TIFF_INCLUDE_DIR}>)
target_link_libraries(misaxx-imaging PUBLIC ${OpenCV_LIBS}
        ${TIFF_LIBRARIES}
        misaxx::misaxx-core)

