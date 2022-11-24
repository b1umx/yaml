#pragma once

#include "forward.hpp"
#include "type.hpp"


namespace b1umx::yaml {


// forward
template<template<typename...> typename Traits>
class basic_value;


template<typename T, typename = void>
struct traits {
};

template<>
struct traits<uninitialized_t> {
    template<template<typename...> typename Traits>
    static void assign(basic_value<Traits> &, uninitialized_t) { 
    }
};

template<>
struct traits<null_t> {
    template<template<typename...> typename Traits>
    static void assign(basic_value<Traits> &v, null_t) {
        v.set_null(); 
    }
};

template<>
struct traits<bool> {
    using type = bool;

    template<template<typename...> typename Traits>
    static void assign(basic_value<Traits>& v, const bool b) {
        v.set_bool(b);
    }

    template<template<typename...> typename Traits>
    static bool as(const basic_value<Traits>& v) {
        return v.get_boolean();
    }
};


}
