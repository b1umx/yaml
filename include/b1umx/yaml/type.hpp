#pragma once

#include <cstdint>


namespace b1umx::yaml {

enum class type: std::size_t {
    UNINITIALIZED,
    NULL_,
    BOOLEAN,
    INTEGER,
    UNSIGNED_INTEGER,
    FLOAT,
    STRING,
    SEQUENCE,
    MAPPING,
    ORDERED_MAPPING
};

struct uninitialized_t {
};

struct null_t {
};

constexpr inline null_t null {};

}
