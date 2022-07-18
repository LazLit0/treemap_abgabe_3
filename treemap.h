// C++ Aufgabe tree_map von Hartmut Schirmacher, BHT Berlin

#pragma once

// other includes
#include <memory>
#include <iostream>
#include <utility>
#include <tuple>
#include <cassert>


// class definitions
#include "treemap_class.h"
#include "treemap_iterator.h"
#include "treemap_node.h"

namespace my {

template<typename K, typename T>
treemap<K,T>::treemap()
{
    size_ = 0;
}

template<typename K, typename T>
void
treemap<K,T>::clear()
{
    root_ = nullptr;
    size_ = 0;
}

// random read-only access to value by key
template<typename K, typename T>
T
treemap<K,T>::operator[](const K& key) const
{
    iterator i = find(key);
    return i->second;
}

// random write access to value by key
template<typename K, typename T>
T&
treemap<K,T>::operator[](const K& key)
{
    auto [i, dummy] = insert(key, T());
    return i->second;
}

// number of elements in map (nodes in tree)
template<typename K, typename T>
size_t
treemap<K,T>::size() const
{
    return size_;
}

// move ctor
template<typename K, typename T>
treemap<K,T>::treemap(treemap<K,T>&& rhs)
{
    swap(*this, rhs);
}

template<typename K, typename T>
void
treemap<K,T>::pre_order_traversal(treemap<K,T>::iterator i, treemap<K,T>& lhs) {
    if(i == iterator(nullptr)) {
        return;
    }
    auto key = i.currentPointr_.lock()->data_.first;
    auto value = i.currentPointr_.lock()->data_.second;
    lhs.insert(key, value);

    treemap<K,T>::pre_order_traversal(i.currentPointr_.lock()->leftChild_, lhs);
    treemap<K,T>::pre_order_traversal(i.currentPointr_.lock()->rightChild_, lhs);
}

// deep copy ctor
template<typename K, typename T>
treemap<K,T>::treemap(const treemap<K,T>& rhs)
{
    // traverse in pre order
    size_ = 0;
    pre_order_traversal(iterator(rhs.root_),*this); 
}

// assignment (move & copy)
template<typename K, typename T>
treemap<K,T>& 
treemap<K,T>::operator=(treemap<K,T> rhs)
{
    clear();
    // create temporary tree
    treemap<K,T>temp = rhs;
    swap(*this, *temp);
    *this = temp;

    return *this;
}


// iterator referencing first element (node) in map
template<typename K, typename T>
typename treemap<K,T>::iterator
treemap<K,T>::begin()
{
    return iterator(root_).min();
}

// iterator referencing no element (node) in map
template<typename K, typename T>
typename treemap<K,T>::iterator
treemap<K,T>::end() const
{
    return iterator(nullptr, root_);
}

// add a new element into the tree
// returns:
// - iterator to element
// - true if element was inserted; false if key was already in map
template<typename K, typename T>
std::pair<typename treemap<K,T>::iterator,bool>
treemap<K,T>::insert(const K& key, const T& value)
{
    /**
     * T < current: left
     * T > current: right
     * T = current: overwrite
     */

    if(size_ == 0)
    {
        root_= std::make_shared<node>(nullptr, std::make_pair(key,value));
        size_++;
        return std::make_pair(iterator(root_), true);
    }

    auto next = root_;
    while(true) {
        // left side
        if(key < next->data_.first) {
            if(next->leftChild_ == nullptr) {
                next->leftChild_ = std::make_shared<node>(next, std::make_pair(key, value));
                size_++;
                return std::make_pair(iterator(next->leftChild_), true);
            }
            next = next->leftChild_;
        
        // right side
        } else if (key > next->data_.first) {
            if(next->rightChild_ == nullptr) {
                next->rightChild_ = std::make_shared<node>(next, std::make_pair(key, value));
                size_++;
                return std::make_pair(iterator(next->rightChild_), true);
            }
            next = next->rightChild_;
        } else {
            return std::make_pair(iterator(next), false);
        }
    }
}

// add a new element into the tree, or overwrite existing element if key already in map
// returns:
// - iterator to element
// - true if element was newly created; false if value for existing key was overwritten
template<typename K, typename T>
std::pair<typename treemap<K,T>::iterator,bool>
treemap<K,T>::insert_or_assign(const K& key, const T&value)
{
    iterator i = find(key);
    if(i == iterator(nullptr)) {
        return insert(key, value);
    }
    i->second = value;
    return std::make_pair(i, false);
}

// find element with specific key. returns end() if not found.
template<typename K, typename T>
typename treemap<K,T>::iterator
treemap<K,T>::find(const K& key) const
{
    auto next = root_;
    while(next != nullptr) {
        if(key < next->data_.first) {
            next = next->leftChild_;
        } else if (key > next->data_.first) {
            next = next->rightChild_;
        } else {
            return iterator(next);
        }
    }
    return iterator(next);
}

// how often is the element contained in the map?
template<typename K, typename T>
size_t
treemap<K,T>::count(const K& key) const
{
    iterator i = find(key);
    if(i == iterator(nullptr)) {
        return 0;
    }
    return 1;
}
// swap is overloaded in global namespace
// see https://stackoverflow.com/questions/11562/how-to-overload-stdswap
// (answer by Attention Mozza314)
template<typename K, typename T>
void
treemap<K,T>::swap(treemap<K,T>& lhs, treemap<K,T>& rhs)
{
    std::swap(lhs.root_, rhs.root_);
    std::swap(lhs.size_, rhs.size_);
}

} // my::
