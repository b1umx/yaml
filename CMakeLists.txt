cmake_minimum_required(VERSION 3.13)

project(byaml
    VERSION 0.1.0
    DESCRIPTION "Library for YAML"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(byaml)
add_library(byaml::byaml ALIAS byaml)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

include(cmake/utils.cmake)
include(GNUInstallDirs)

option(BYAML_BUILD_TESTS "Build byaml tests" OFF)
option(BYAML_BUILD_EXAMPLES "Build byaml examples" OFF)
option(BYAML_INSTALL "Generate target for installing byaml" ${is_top_level})
set_if_undefined(BYAML_INSTALL_CMAKEDIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/byaml-${PROJECT_VERSION}" CACHE STRING
    "Install path for byaml package-related CMake files")

if(DEFINED BYAML_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${BYAML_SHARED_LIBS})
endif()


set(public_headers
    include/byaml/yaml.hpp
    include/byaml/ordered_map.hpp)
set(sources
    ${public_headers}
    src/detail/node.cpp
    src/yaml.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})


include(CMakePackageConfigHelpers)

target_sources(byaml PRIVATE ${sources})
target_compile_features(byaml PUBLIC cxx_std_17)
target_include_directories(byaml
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(byaml PROPERTIES
    PUBLIC_HEADER "${public_headers}"
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(BYAML_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BYAML_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

