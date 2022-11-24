#include <iostream>
#include <b1umx/yaml.hpp>


int main() {
    using namespace b1umx::yaml;
    value bv(true);
    value bn(null);
    std::cout << "bool: " << bv.as<bool>() << '\n';
    // std::cout << "null: " << bn.as<null_t>() << '\n';  -- use of deleted function compilation error
}
