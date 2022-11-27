#include <iostream>
#include <b1umx/yaml.hpp>


int main() {
    using namespace std;
    using namespace b1umx::yaml;
    value bv(true);
    value bs(std::string("hello"));
    std::cout << "bool: " << bv.as<string>() << '\n';
    std::cout << "string: " << bs.as<string>() << '\n';
    // std::cout << "null: " << bn.as<null_t>() << '\n';  -- use of deleted function compilation error
}
