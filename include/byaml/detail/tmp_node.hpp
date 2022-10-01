#pragma once

#include <utility>
#include <initializer_list>
#include <type_traits>


namespace byaml {


template<typename NodeType>
class TmpNode {
public:
    TmpNode(NodeType &&value):
        ownedValue(std::move(value)) {
    }

    TmpNode(const NodeType &value):
        refValue(&value) {
    }

    TmpNode(std::initializer_list<TmpNode> list):
        ownedValue(list) {
    }

    template<typename... Args, typename = std::enable_if_t<std::is_constructible_v<NodeType, Args...>>>
    TmpNode(Args &&... args):
        ownedValue(std::forward<Args>(args)...) {
    }

    ~TmpNode() = default;
    TmpNode(TmpNode &&) = default;
    
    TmpNode(const TmpNode &) = delete;
    TmpNode & operator=(const TmpNode &) = delete;
    TmpNode & operator=(TmpNode &&) = delete;

    NodeType take() const {
        return refValue == nullptr ? std::move(ownedValue) : *refValue;
    }

    const NodeType & operator*() const {
        return refValue == nullptr ? ownedValue : *refValue;
    }

    const NodeType * operator->() const {
        return &**this;
    }
 
private:
    NodeType ownedValue;
    const NodeType *refValue = nullptr;
};


}

