#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <stdexcept>
#include <memory>
#include <string>
#include "./iterators/vector_iterator.hpp"
#include "./iterators/reverse_iterator.hpp"
#include "pair.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

namespace ft {

template< typename Key, typename T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>> >
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
    explicit map(const key_compare &comp = Compare(), const allocator_type& = Allocator()) {}
    
    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare& comp = Compare(), const allocator_type& = Allocator()) {}

    map (const  ft::map<key_type, mapped_type, key_compare, allocator_type> &src ) { 
        if (this != &src)
            *this = src;
    }

};
}

#endif