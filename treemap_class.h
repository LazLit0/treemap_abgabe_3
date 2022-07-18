// C++ Aufgabe tree_map von Hartmut Schirmacher, BHT Berlin
// treemap_class.h - these class definitions are included in all treemap header files

#pragma once


namespace my {

/*
 * class treemap<K,T>
 * represents an associative container (dictionary) with unique keys
 * implemented by a binary search tree
 *
 */
template<typename K, typename T>
class treemap
{
public:

    // public type aliases
    using key_type = K;
    using mapped_type = T;
    using value_type = std::pair<K, T>;

protected:
    // protected inner class node is defined in a separate header file
    class node;
    std::shared_ptr<node> root_;
    size_t size_; 

public:
    // public inner class iterator is defined in a separate header file 
    class iterator; 

    // used for copy&move
    static void swap(treemap<K,T>& , treemap<K,T>& );

    // construct empty map
    treemap();

    // move ctor
    treemap(treemap<K,T>&&);

    // helper for pre order traversal
    void pre_order_traversal(iterator i, treemap& lhs);

    // deep copy ctor
    treemap(const treemap<K,T>&);

    // how often is the element contained in the map?
    // (for this type of container, can only return 0 or 1)
    size_t count(const K&) const;

    // assignment (move & copy)
    treemap<K,T>& operator=(treemap<K,T>);

    // remove/destroy all elements
    void clear();

    // random read-only access to value by key, does not modify map
    T operator[](const K& ) const;

    // random write access to value by key
    T& operator[](const K&);

    // number of elements in map (nodes in tree)
    size_t size() const;

    // iterator referencing first element (node) in map
    iterator begin();

    // iterator referencing no element (node) in map
    iterator end() const;

    // add a new element into the tree
    // returns pair, consisting of:
    // - iterator to element
    // - bool
    //   - true if element was inserted;
    //   - false if key was already in map (will not overwrite existing value)
    std::pair<iterator,bool> insert(const K&, const T&);

    // add a new element into the tree, or overwrite existing element if key already in map
    // returns:
    // - iterator to element
    // - true if element was newly created; false if existing element was overwritten
    std::pair<iterator,bool> insert_or_assign(const K&, const T&);

    // find element with specific key. returns end() if not found.
    iterator find(const K&) const;

};


} // namespace my

