#ifndef VECTOR_HPP
# define VECTOR _HPP

#include <iostream>
#include <memory>
#include <vector>
namespace ft {
    
template<Typename T, class Allocator = std::allocator<T> >
class vector {
public:
    //  types:
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    //typedef implementation defined iterator; 
    //typedef implementation defined const_iterator; 
    typedef std::size_t size_type; 
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    //typedef ft::reverse_iterator<iterator> reverse_iterator;
    //typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    // construct/destroy:
    explicit vector::vector(const allocator_type &allocator = Allocator()) {}
    explicit vector::vector(size_type n, const value_type& value = value_type(), const allocator_type &allocator = Allocator()) {}
    
    template <Typename InputIterator>
    vector::vector (InputIterator first, InputIterator last, const allocator_type &allocator = Allocator()) {}
    vector::vector (vector<T, allocator_type> const& src) {}




};

}

#endif;