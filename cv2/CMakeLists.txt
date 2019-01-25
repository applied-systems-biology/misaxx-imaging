cmake_minimum_required(VERSION 3.11)
project(misaxx-imaging-sopencv LANGUAGES CXX VERSION 0.1.0 DESCRIPTION "Static OpenCV")

include(FetchContent)
include(FeatureSummary)
include(GenerateExportHeader)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Build options
option(BUILD_SHARED_LIBS "Build shared library" ON)

find_package(Boost 1.63 COMPONENTS REQUIRED filesystem regex)
find_package(OpenCV 4 COMPONENTS REQUIRED core imgproc ximgproc imgcodecs highgui)
find_package(TIFF REQUIRED)
feature_summary(WHAT ALL)

add_library(misaxx-static-opencv include/misaxx/imaging/utils/cv2/BMat.h
        src/BMat.cpp
        src/images/G_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_BMat.h
        src/images/G_xU_xS_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_xU_xS_BMat.h
        src/images/G_xF_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_xF_BMat.h
        src/images/G_32F_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_32F_BMat.h
        src/images/G_8U_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_8U_BMat.h
        src/images/BGR_8U_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/BGR_8U_BMat.h
        include/misaxx/imaging/utils/cv2/SMat.h
        src/images/G_8S_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_8S_BMat.h
        src/images/G_16S_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_16S_BMat.h
        src/images/G_16U_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_16U_BMat.h
        src/images/G_64F_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_64F_BMat.h
        src/images/G_32S_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_32S_BMat.h
        src/io/tiffio.cpp
        include/misaxx/imaging/utils/cv2/io/tiffio.h
        include/misaxx/imaging/utils/cv2/static_types.h
        src/toolbox/toolbox_binarize.cpp
        include/misaxx/imaging/utils/cv2/toolbox/toolbox_binarize.h
        src/toolbox/toolbox_semantic_convert.cpp
        include/misaxx/imaging/utils/cv2/toolbox/toolbox_semantic_convert.h
        src/images/G_xU_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_xU_BMat.h
        src/images/G_xS_BMat.cpp
        include/misaxx/imaging/utils/cv2/images/G_xS_BMat.h
        src/toolbox/toolbox_query.cpp
        include/misaxx/imaging/utils/cv2/toolbox/toolbox_query.h)

# For installation
target_compile_features(misaxx-static-opencv PUBLIC cxx_std_17)
add_library(misaxx::misaxx-static-opencv ALIAS misaxx-static-opencv)

generate_export_header(misaxx-static-opencv
        EXPORT_MACRO_NAME MISAXX_STATIC_OPENCV_API
        EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/misaxx/common.h
        )
target_include_directories(misaxx-static-opencv
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
# Additional warnings
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(misaxx-static-opencv PRIVATE -Wredundant-decls
            -Wcast-align
            -Wmissing-declarations
            -Wmissing-include-dirs
            -Wswitch-enum
            -Wswitch-default
            -Wextra
            -Wall
            -Winvalid-pch
            -Wredundant-decls)
endif()

# Include dependencies
target_include_directories(misaxx-static-opencv PUBLIC $<BUILD_INTERFACE:${OpenCV_INCLUDE_DIR}>)
target_include_directories(misaxx-static-opencv PUBLIC $<BUILD_INTERFACE:${TIFF_INCLUDE_DIR}>)
target_link_libraries(misaxx-static-opencv PUBLIC ${OpenCV_LIBS}
        ${TIFF_LIBRARIES}
        Boost::filesystem
        Boost::regex)

# Installation
set_target_properties(misaxx-static-opencv PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        )
install(TARGETS misaxx-static-opencv
        EXPORT misaxx-static-opencv-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${LIBLEGACY_INCLUDE_DIRS}
        )
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/misaxx
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
install(DIRECTORY ${CMAKE_BINARY_DIR}/include/misaxx
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
install(EXPORT misaxx-static-opencv-targets
        FILE misaxx-static-opencv-targets.cmake
        NAMESPACE misaxx::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/misaxx-static-opencv
        )
configure_package_config_file(
        ${CMAKE_SOURCE_DIR}/cmake/misaxx-static-opencv-config.cmake.in
        ${CMAKE_BINARY_DIR}/cmake/misaxx-static-opencv-config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/misaxx-static-opencv
)
write_basic_package_version_file(
        ${CMAKE_BINARY_DIR}/cmake/misaxx-static-opencv-config-version.cmake
        VERSION ${misaxx-static-opencv_VERSION}
        COMPATIBILITY AnyNewerVersion
)
install(
        FILES
        ${CMAKE_BINARY_DIR}/cmake/misaxx-static-opencv-config.cmake
        ${CMAKE_BINARY_DIR}/cmake/misaxx-static-opencv-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/misaxx-static-opencv
)
