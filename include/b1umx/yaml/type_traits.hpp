#pragma once

#include "is_valid.hpp"


namespace b1umx::yaml::internal {


template<typename...>
inline constexpr bool has_as_impl = false;

template<typename Trait, typename... Args>
inline constexpr bool has_as_impl<decltype((void)Trait::as(std::declval<Args>()...)), Trait, Args...> = true;




}
