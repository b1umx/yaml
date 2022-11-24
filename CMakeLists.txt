cmake_minimum_required(VERSION 3.13)

project(b1umx_yaml
    VERSION 0.1.0
    DESCRIPTION "Library for YAML"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(B1UMX_YAML_TARGET_NAME ${PROJECT_NAME})

add_library(${B1UMX_YAML_TARGET_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${B1UMX_YAML_TARGET_NAME} ALIAS ${B1UMX_YAML_TARGET_NAME})

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

include(cmake/utils.cmake)
include(GNUInstallDirs)

option(B1UMX_YAML_BUILD_TESTS "Build b1umx_yaml tests" OFF)
option(B1UMX_YAML_BUILD_EXAMPLES "Build b1umx_yaml examples" OFF)
option(B1UMX_YAML_INSTALL "Generate target for installing b1umx_yaml" ${is_top_level})
set_if_undefined(B1UMX_YAML_INSTALL_CMAKEDIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/b1umx_yaml-${PROJECT_VERSION}" CACHE STRING
    "Install path for b1umx_yaml package-related CMake files")

if(DEFINED B1UMX_YAML_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${B1UMX_YAML_SHARED_LIBS})
endif()


set(public_headers
    include/b1umx/yaml.hpp)
set(sources
    ${public_headers})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

include(CMakePackageConfigHelpers)

target_sources(${B1UMX_YAML_TARGET_NAME} PRIVATE ${sources})
target_compile_features(${B1UMX_YAML_TARGET_NAME} INTERFACE cxx_std_17)
target_include_directories(${B1UMX_YAML_TARGET_NAME}
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

set_target_properties(${B1UMX_YAML_TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${public_headers}"
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(B1UMX_YAML_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(B1UMX_YAML_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

