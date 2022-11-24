cmake_minimum_required(VERSION 3.13)

project(b1umx_yaml_example LANGUAGES CXX)


string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
    is_top_level)

if(is_top_level)
    find_package(b1umx_yaml REQUIRED)
endif()

set(sources main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(b1umx_yaml_example)
target_sources(b1umx_yaml_example PRIVATE ${sources})
target_link_libraries(b1umx_yaml_example
    PRIVATE b1umx_yaml::b1umx_yaml)
