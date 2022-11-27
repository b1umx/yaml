#pragma once

#include <memory>
#include <vector>


namespace b1umx::yaml {


template<typename Key, typename T, typename Allocator = std::allocator<std::pair<const Key, T>>>
class omap {
    using value_t = std::pair<const Key, T>;
    using container_t = std::vector<value_t>;

private:
    container_t _container; 

public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = value_t;
    using size_type = typename container_t::size_type;
    using difference_type = typename container_t::difference_type;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = std::allocator_traits<Allocator>::pointer;
    using const_pointer = std::allocator_traits<Allocator>::const_pointer;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
    using reverse_iterator = typename container_t::reverse_iterator;
    using const_reverse_iterator = typename container_t::const_reverse_iterator;

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

    bool empty() const {
        return _container.empty();
    }

    size_t size() const {
        return _container.size();
    } 
};


}
