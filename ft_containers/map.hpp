#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <stdexcept>
#include <memory>
#include <string>
#include "./iterators/map_iterator.hpp"
#include "./iterators/reverse_iterator.hpp"
#include "pair.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

namespace ft {

template< typename Key, typename T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T>> >
class map {
public:
    //types:
    typedef Key key_type;
    typedef T mapped_type;
    typedef typename ft::pair<const key_type, mapped_type> value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef map_iterator<value_type> iterator; 
    typedef map_iterator<const value_type> const_iterator; 
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    //class value_compare
    class value_compare : public std::binary_function<value_type, value_type, bool> {
        friend class map;
    protected:
        Compare comp;
        value_compare(Compare c) : comp(c) {}
    public:
        bool operator()(const value_type &x, const value_type &y) const { return comp(x.first, y.first); }
    };

    //constructors
    explicit map(const key_compare &comp = Compare(), const allocator_type &alloc = Allocator()) : _comp(comp), _alloc(alloc), _nodeAlloc(), _size(0) {
        _root = _nodeAlloc.allocate(1);
        _alloc.construct(_root, Node());
        _leaf = _nodeAlloc.allocate(1);
        _leaf.construct(_leaf, Node());
        _root->right = _leaf;
        _leaf->parent = _root;
    }
    
    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare& comp = Compare(), const allocator_type& = Allocator()) {}

    map (const  ft::map<key_type, mapped_type, key_compare, allocator_type> &src ) { 
        if (this != &src)
            *this = src;
    }

    //modifiers
    ft::pair<iterator, bool> insert(value_type const &value) {
        iterator it;
        Node *actual = 
        return ft::make_pair(it, true);
    }

    protected:
        typedef typename ft::AVLtree<value_type> Node;
        typedef typename allocator_type::rebind<Node>::other node_allocator_type;

        Node *rotateLeft() {}
        Node *rotateRight() {}
        void *ajustHeight() {}
        void balanceTree() {}

    private:
       
        Node *_root;
        Node *_leaf;
        size_type _size;
        allocator_type _alloc;
        node_allocator_type _nodeAlloc;
        key_compare _comp;


};
}

#endif