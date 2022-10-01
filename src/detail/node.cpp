#include <byaml/detail/node.hpp>

#include <byaml/utils.hpp>



using namespace std;
using namespace byaml::utils;

namespace byaml {


Node::Node(Node &&other):
    _data(move(other._data)) {
}


Node::Node(const Node &other):
    _data(other._data) {
}


Node::~Node() = default;


Node & Node::operator=(Node &&rhs) {
    *_data = move(rhs._data);
    return *this;
}


Node & Node::operator=(const Node &rhs) {
    if (this != &rhs)
        *_data = *rhs._data;
    return *this;
}


Node Node::clone() const {
    Node resultNode;
    if (_data)
        resultNode._data = make_shared<ValueType>(*_data);
    return resultNode;
}


Node Node::operator[](size_t index) {
    Node result;
    if (!_data)
        _data = make_shared<ValueType>(Sequence());
    
    if (holds_alternative<Sequence>(*_data)) {
        auto sequence = get<Sequence>(*_data);
        if (sequence.size() <= index)
            for (size_t i = sequence.size(); i <= index; i++)
                 sequence.emplace_back();
        result = sequence[index];
    }
    return result;
}


Node Node::operator[](size_t index) const {
    Node result;
    if (_data && holds_alternative<Sequence>(*_data)) {
        const auto sequence = get<Sequence>(*_data);
        if (index < sequence.size())
            result = sequence[index];
    }
    return result;
}


Node Node::operator[](const string &key) {
    Node result;
    if (!_data)
        _data = make_shared<ValueType>(OrderedMapping());

    if (holds_alternative<OrderedMapping>(*_data)) {
        auto orderedMapping = get<OrderedMapping>(*_data);
        auto it = find_if(orderedMapping.begin(), orderedMapping.end(), [&](const auto &kv) {
            return kv.first == key;
        });
        if (it == orderedMapping.end()) {
            orderedMapping.emplace_back(key);
            result = orderedMapping.back().second;
        }
        else
            result = it->second;
    }
    else if (holds_alternative<Mapping>(*_data)) {
        auto mapping = get<Mapping>(*_data);
        result = mapping[key];
    }
    return result;
}


Node Node::operator[](const string &key) const {
    Node result;
    if (_data) {
        if (holds_alternative<OrderedMapping>(*_data)) {
            const auto orderedMapping = get<OrderedMapping>(*_data);
            auto it = find_if(orderedMapping.cbegin(), orderedMapping.cend(), [&](const auto &kv) {
                return kv.first == key;
            });
            if (it != orderedMapping.end())
                result = it->second;
        }
    }
    else if (holds_alternative<Mapping>(*_data)) {
        const auto mapping = get<Mapping>(*_data);
        auto it = mapping.find(key);
        if (it != mapping.end())
            result = it->second;
    }
    return result;
}


bool Node::isUndefined() const {
    return !_data;
}


string Node::type() const {
    string result;
    if (_data)
        visit(Overloaded {
            [&](const Null)             { result = "null"; },
            [&](bool)                   { result = "boolean"; },
            [&](int64_t)                { result = "integer"; },
            [&](double)                 { result = "floating point"; },
            [&](const String &)         { result = "string"; },
            [&](const Sequence &)       { result = "sequence"; },
            [&](const Mapping &)        { result = "mapping"; },
            [&](const OrderedMapping &) { result = "ordered mapping"; },
        }, *_data);
    else
        result = "undefined";
    return result;
}


}

