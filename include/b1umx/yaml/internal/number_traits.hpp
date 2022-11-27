#pragma once

#include "../forward.hpp"


namespace b1umx::yaml::internal {


template<typename T>
struct number_trait {
};

template<typename T>
struct signed_trait: number_trait<T> {
    template<template<typename...> typename Traits>
    static void assign(basic_value<Traits>& v, const T i) {
        v.set_int(i);
    }
};

template<typename T>
struct unsigned_trait: number_trait<T> {
    template<template<typename...> typename Traits>
    static void assign(basic_value<Traits>& v, const T u) {
        v.set_uint(u);
    }
};

template<typename T>
struct float_trait: number_trait<T> {
    template<template<typename...> typename Traits>
    static void assign(basic_value<Traits>& v, const T f) {
        v.set_float(f);
    }
};


}
