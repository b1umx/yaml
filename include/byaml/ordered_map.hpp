#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <utility>
#include <vector>


namespace byaml {


template<typename Key, typename T>
class OrderedMap: public std::vector<std::pair<Key, T>> {
private:
    using Container = std::vector<std::pair<Key, T>>;
    using key_type = Key;
    using mapped_type = T;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using size_type = typename Container::size_type;
    using value_type = typename Container::value_type;

public:
    OrderedMap() = default;
    OrderedMap(std::initializer_list<value_type> init) {
        for (const auto &element: init) {
            auto it = std::find_if(this->begin(), this->end(), [&](const auto &emplacedElement) {
                return emplacedElement.first == element.first;
            });
            if (it == this->end())
                this->push_back(element);
            else
                it->second = element.second;
        }
    }
};


} // namespace byaml

