// C++ Aufgabe tree_map von Hartmut Schirmacher, BHT Berlin

#pragma once

// class definitions
#include "treemap_class.h"

namespace my {

    // iterator: references a node within the tree
    template<typename K, typename T>
    class treemap<K,T>::iterator {
    protected:

        // treemap is a friend, can call protected constructor
        friend class treemap;
        std::weak_ptr<node> currentPointr_;
        std::weak_ptr<node> rootPointr_;

        // construct iterator referencing a speciic node
        // - only treemap shall be allowed to do so
        iterator(std::shared_ptr<node> start, std::shared_ptr<node> root = nullptr)
        {
            currentPointr_ = start;
            rootPointr_ = root;
        }

        // non-owning reference to the actual node
        iterator() {};

        iterator min()
        {
            auto current = currentPointr_.lock();
            while(current->leftChild_ != nullptr) {
                current = current->leftChild_;
            }
            return current;
        }

        iterator max()
        {
            auto current = currentPointr_.lock();
            while(current->rightChild_ != nullptr) {
                current = current -> rightChild_;
            }
            return current;
        }

    public:

        // access data of referenced map element (node)
        value_type& operator*()
        {
            return currentPointr_.lock() -> data_;
        }
        value_type* operator->()
        {
            return &(currentPointr_.lock() -> data_);
        }

        // two iterators are equal if they point to the same node
        bool operator==(const iterator& rhs) const
        {
            return currentPointr_.lock() == rhs.currentPointr_.lock();
        }

        bool operator!=(const iterator& rhs) const
        {
            return !(*this == rhs);
        }

        // next element in map, pre-increment
        // note: must modify self!
        iterator& operator++()
        {
            auto current = currentPointr_.lock();
            if(current->rightChild_ != nullptr)
            {
                // weak_ptr auf linkes element, also kleinste Zahl
                currentPointr_ = iterator(current->rightChild_).min().currentPointr_.lock();
                return *this;
            }

            auto parent = current->parent_.lock();
            while (parent != nullptr && current == parent->rightChild_)
            {
                current = parent;
                parent = parent->parent_.lock();
            }
            currentPointr_ = parent;
            return *this;
            
        }

        // prev element in map, pre-decrement
        // note: must modify self!
        iterator& operator--()
        {
            auto current = currentPointr_.lock();
            if(current == nullptr) {
                currentPointr_ = iterator(rootPointr_.lock()).max().currentPointr_.lock();
                return *this;
            }
            if(current->leftChild_ != nullptr) {
                currentPointr_ = iterator(current->leftChild_).max().currentPointr_.lock();
                return *this;
            }

            auto pointr = current->parent_.lock();
            while(pointr != nullptr && current == pointr->leftChild_)
            {
                current = pointr;
                pointr = pointr->parent_.lock();
            }
            currentPointr_ = pointr;
            return *this;
        }

    }; // class iterator

} // my::

