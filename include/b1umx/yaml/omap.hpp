#pragma once

#include <memory>
#include <vector>


namespace b1umx::yaml {


template<typename Key, typename T, typename Allocator = std::allocator<std::pair<const Key, T>>>
class omap {
    using value_t = std::pair<Key, T>;
    using container_t = std::vector<value_t>;

private:
    container_t _container; 

    // using Container = std::vector<std::pair<Key, T>>;
    // using key_type = Key;
    // using mapped_type = T;
    // using iterator = typename Container::iterator;
    // using const_iterator = typename Container::const_iterator;
    // using size_type = typename Container::size_type;
    // using value_type = typename Container::value_type;

public:
    omap() = default;
    // omap(std::initializer_list<value_type> init) {
    //     for (const auto &element: init) {
    //         auto it = std::find_if(this->begin(), this->end(), [&](const auto &emplacedElement) {
    //             return emplacedElement.first == element.first;
    //         });
    //         if (it == this->end())
    //             this->push_back(element);
    //         else
    //             it->second = element.second;
    //     }
    // }
};


}
