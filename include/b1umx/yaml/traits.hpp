#pragma once

#include "forward.hpp"
#include "type.hpp"


namespace b1umx::yaml {


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
    template<template<typename...> typename Traits>
    static void assign(basic_value<Traits>& v, const bool b) {
        v.set_bool(b);
    }
};

template<> struct traits<signed char>: internal::signed_trait<signed char> {};
template<> struct traits<signed short>: internal::signed_trait<signed short> {};
template<> struct traits<signed int>: internal::signed_trait<signed int> {};
template<> struct traits<signed long>: internal::signed_trait<signed long> {};
template<> struct traits<signed long long>: internal::signed_trait<signed long long> {};

template<> struct traits<unsigned char>: internal::unsigned_trait<unsigned char> {};
template<> struct traits<unsigned short>: internal::unsigned_trait<unsigned short> {};
template<> struct traits<unsigned int>: internal::unsigned_trait<unsigned int> {};
template<> struct traits<unsigned long>: internal::unsigned_trait<unsigned long> {};
template<> struct traits<unsigned long long>: internal::unsigned_trait<unsigned long long> {};

template<> struct traits<float>: internal::float_trait<float> {};
template<> struct traits<double>: internal::float_trait<double> {};

template<>
struct traits<std::string> {
    template<template<typename...> typename Traits>
    static void assign(basic_value<Traits>& v, const std::string s) {
        v.set_string(s);
    }
};

template<>
struct traits<const char*> {
    template<template<typename...> typename Traits>
    static void assign(basic_value<Traits>& v, const char* s) {
        v.set_string(s);
    }
};


}
