#include <map>
#include <variant>
#include <vector>
#include <string>
#include <type_traits>

#include "forward.hpp"
#include "omap.hpp"
#include "type.hpp"
#include "internal/type_traits.hpp"
#include "internal/number_traits.hpp"



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

    void set_int(const int64_t i) {
        _container = i;
    }

    void set_uint(const uint64_t u) {
        _container = u;
    }

    void set_float(const double f) {
        _container = f;
    }

    void set_string(const std::string &s) {
        _container = s;
    }

    yaml::type type() const {
        return static_cast<yaml::type>(_container.index());
    }

    bool is_null() const {
        return std::holds_alternative<null_t>(_container);
    }

    bool is_bool() const {
        return std::holds_alternative<bool>(_container);
    }

    bool is_string() const {
        return std::holds_alternative<std::string>(_container);
    }

    bool get_bool() const {
        return std::get<bool>(_container);
    }

    int64_t get_int() const {
        return std::get<int64_t>(_container);
    }

    uint64_t get_uint() const {
        return std::get<uint64_t>(_container);
    }

    double get_float() const {
        return std::get<double>(_container);
    }

    std::string& get_string() & {
        return std::get<std::string>(_container);
    }

    std::string&& get_string() && {
        return std::get<std::string>(_container);
    }

    const std::string& get_string() const& {
        return std::get<std::string>(_container);
    }

    sequence_t& get_seq() & {
        return std::get<sequence_t>(_container);
    }

    sequence_t&& get_seq() && {
        return std::get<sequence_t>(_container);
    }

    const sequence_t& get_seq() const& {
        return std::get<sequence_t>(_container);
    }

    mapping_t& get_map() & {
        return std::get<mapping_t>(_container);
    }

    mapping_t&& get_map() && {
        return std::get<mapping_t>(_container);
    }

    const mapping_t& get_map() const& {
        return std::get<mapping_t>(_container);
    }

    omapping_t& get_omap() & {
        return std::get<omapping_t>(_container);
    }

    omapping_t&& get_omap() && {
        return std::get<omapping_t>(_container);
    }

    const omapping_t& get_omap() const& {
        return std::get<omapping_t>(_container);
    }

    template<typename T>
    std::enable_if_t<internal::has_as<Traits<T>, basic_value>, T> as() const {
        return Traits<T>::as(*this);
    }

    template<typename T>
    std::enable_if_t<!internal::has_as<Traits<T>, basic_value>, T> as() = delete;
};


}
