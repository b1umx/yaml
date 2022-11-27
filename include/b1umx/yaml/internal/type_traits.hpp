#pragma once

#include <type_traits>


namespace b1umx::yaml::internal {


// check Trait::as(const Value &)
template<typename, typename, typename = std::void_t<>>
struct has_as_t: std::false_type {
};

template<typename Trait, typename Value>
struct has_as_t<Trait, Value,
    std::void_t<decltype(Trait::as(std::declval<Value>()))>>: std::true_type {
};


}
