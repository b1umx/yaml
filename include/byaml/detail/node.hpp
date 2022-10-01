#pragma once

#include <cstdint>
#include <initializer_list>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#include <byaml/ordered_map.hpp>
#include <byaml/detail/tmp_node.hpp>


namespace byaml {


class Node {
    struct Null {};
    using String = std::string;
    using StringPtr = std::unique_ptr<String>;
    using Sequence = std::vector<Node>;
    using SequencePtr = std::unique_ptr<Sequence>;
    using Mapping = std::map<std::string, Node>;
    using MappingPtr = std::unique_ptr<Mapping>;
    using OrderedMapping = OrderedMap<std::string, Node>;
    using OrderedMappingPtr = std::unique_ptr<OrderedMapping>;

    using ValueType = std::variant<
        Null,
        bool,
        std::int64_t,
        double,
        StringPtr,
        SequencePtr,
        MappingPtr,
        OrderedMappingPtr
    >;

    using InitializerListTmpNode = std::initializer_list<TmpNode<Node>>;
    using InitializerListTmpMap = std::initializer_list<std::pair<std::string, TmpNode<Node>>>;

public:
    Node() = default;
    Node(Node &&other);
    Node(const Node &other);
    template<typename T, typename = std::enable_if_t<!std::is_same_v<Node, std::decay_t<T>>>>
    Node(T &&value) {
        _data = std::make_unique<ValueType>(std::forward<T>(value));
    }
    ~Node();

    Node & operator=(Node &&);
    Node & operator=(const Node &);
    template<typename T, typename = std::enable_if_t<!std::is_same_v<Node, std::decay_t<T>>>>
    Node & operator=(T &&value) {
        *_data = value;
        return *this;
    }

    Node clone() const;
    Node operator[](std::size_t index);
    Node operator[](std::size_t index) const;
    Node operator[](const std::string &key);
    Node operator[](const std::string &key) const;

    bool isUndefined() const;
    std::string type() const;

private:
    std::shared_ptr<ValueType> _data;
};



} // namespace b1umx

