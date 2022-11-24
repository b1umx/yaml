#include <iostream>
#include <b1umx/yaml.hpp>
#include <b1umx/yaml/type_traits.hpp>


int main() {
    using namespace b1umx::yaml;
    // b1umx::yaml::value v(false);
    // std::cout << "is null: " << v.is_null() << '\n';
    // std::cout << "is bool: " << v.is_bool() << '\n';
    std::cout << "bool has as: " << internal::has_as(internal::type<traits<bool>>) << '\n';
    std::cout << "null has as: " << internal::has_as(internal::type<traits<null_t>>) << '\n';
}
