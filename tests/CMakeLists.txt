cmake_minimum_required(VERSION 3.13)
project(byaml-tests)
include("../cmake/utils.cmake")

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

if (is_top_level)
    enable_testing()
    find_package(byaml REQUIRED)
endif()

set(sources
    test_node.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(byaml-tests)
target_sources(byaml-tests PRIVATE ${sources})

Include(FetchContent)
FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.1.0)
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)  

target_link_libraries(byaml-tests
    PRIVATE
        byaml::byaml
        Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(byaml-tests)

