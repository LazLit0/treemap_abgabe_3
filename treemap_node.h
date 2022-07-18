// C++ Aufgabe treemap von Hartmut Schirmacher, BHT Berlin

#pragma once

// class definitions
#include "treemap_class.h"
#include <memory>



namespace my {

    // this is an inner class of class my::tree_map
    template<typename K, typename T>
    class treemap<K,T>::node 
        : public std::enable_shared_from_this<node> 
    {

    public:
    std::pair<K, T> data_;
    std::weak_ptr<node> parent_;
    std::shared_ptr<node> leftChild_;
    std::shared_ptr<node> rightChild_;

    node(std::shared_ptr<node> parent, std::pair<K,T> data) {
        parent_ = parent;
        data_ = data;
    }
    };



} // my::