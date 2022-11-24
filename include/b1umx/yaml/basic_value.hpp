#include <map>
#include <variant>
#include <vector>
#include <string>
#include <type_traits>

#include "omap.hpp"
#include "type.hpp"



namespace b1umx::yaml {


template<template<typename...> typename Traits>
class basic_value {
public:
    using sequence_t = std::vector<basic_value>;
    using mapping_t = std::map<std::string, basic_value, std::less<>>;
    using omapping_t = omap<std::string, basic_value>;

private:
    using container_t = std::variant<
        uninitialized_t,
        null_t,
        bool,
        std::int64_t,
        std::uint64_t,
        double,
        std::string,
        sequence_t,
        mapping_t,
        omapping_t
    >;

    container_t _container;

public:
    basic_value() = default;
    basic_value(const basic_value&) = default;
    basic_value(basic_value&&) = default;

    template<typename T,
             typename D = std::decay_t<T>,
             typename = decltype(Traits<D>::assign(std::declval<basic_value&>(), std::declval<T&&>()))>
    basic_value(T&& v) {
        Traits<D>::assign(*this, std::forward<T>(v));
    }

    void set_null() {
        _container = null;
    }

    void set_bool(const bool b) {
        _container = b;
    }

    bool is_null() const {
        return std::holds_alternative<null_t>(_container);
    }

    bool is_bool() const {
        return std::holds_alternative<bool>(_container);
    }

    bool get_boolean() const {
        bool result {};
        if (std::holds_alternative<bool>(_container)) {
            result = std::get<bool>(_container);
        }
        return result;
    }
};


}
