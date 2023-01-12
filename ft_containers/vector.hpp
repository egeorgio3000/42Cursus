#ifndef VECTOR_HPP
# define VECTOR _HPP

#include <iostream>
#include <memory>
#include <vector>
#include "vector_iterator.hpp"
namespace ft {
    
template<typename T, class Allocator = std::allocator<T> >
class vector {
public:
    //  types:
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    typedef T* iterator; 
    typedef const T* const_iterator; 
    typedef std::size_t size_type; 
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    // construct/destroy:
    explicit vector(const allocator_type &allocator = Allocator()) : _alloc(allocator), _size(0), _capacity(0), _p(NULL) {    }
    explicit vector(size_type n, const value_type& value = value_type(), const allocator_type &allocator = Allocator()) : _alloc(allocator), _size(n), _capacity(n) {
        _p = _alloc.allocate(n);
        for (size_type i = 0; i < n; i++) {
            _alloc.construct(_p, value);
        }

    }
    
    template <typename InputIterator>
    vector(InputIterator first, InputIterator last, const allocator_type &allocator = Allocator()) : _alloc(allocator), _size(0), capacity(0), _p(NULL) {
        InputIterator it = first;
        for(; it != last; it++)
            this->push_back(*it);
    }
    
    vector(ft::vector<T, allocator_type> const& src) {}
    ~vector() {}

    //operators
    ft::vector<T, allocator_type> &operator=(ft::vector<T, allocator_type> const &rhs) {}

    //setters
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last) {
        this->erase(this->begin(), this->end());
        this->insert(this->begin(), first, last);
    }
    void assign(size_type n, const T& u) {
        this->erase(this->begin(), this->end());
        this->insert(begin(),n, u);
    }

    //getters
    allocator_type  get_allocator() const { return _alloc; }

    //member functions
        //modify vector
    iterator insert(iterator position, const T& x) {
        this->push_back(x);
        for (iterator it = this->end() - 1; it != position; it--)
            this->in_swap(it + 1, it);
        return (position);
    }

    void insert(iterator position, size_type n, const T& x) {
        if (n && 2 * _capacity < n + _size)
            reserve(n + _size);
        for (size_type i = 0; i < n; i++)
            insert(position + i, x);
    }

    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last) {
        size_type n = last - first;
        if (n && 2 * _capacity < n + _size)
            reserve(n + _size);
        for (size_type i = 0; i < n; i++)
            insert(position + i, *(first + i));     
    }

    void push_back(const T&value) {
        if ( _size + 1 > _capacity ) {
            if (!_capacity)
                reserve(1);
            else
                reserve(_capacity * 2);
            _alloc.construct(this->end(), value);
            _size += 1;
        }
    }
        //capacity
    size_t max_size() const { return _alloc.max_size(); }
    void reserve( size_type new_cap ) {
        if ( new_cap > max_size() ) { throw std::length_error; }
        if ( new_cap > _capacity ) {
            pointeur new_p = _alloc.allocate( new_cap );
            for (size_type i = 0; i < size(); i++) {
                _alloc.construct(new_p + i, *(_p + i));
                _alloc.destroy(_p + i);

            }
            _alloc.deallocate(_p, _capacity);
            _p = new_p;
            _capacity = new_cap;
        } 
    }

    // iterators:
    iterator begin() { return iterator(_p); }
    const_iterator begin() const { return const_iterator(_p); }
    iterator end() { return iterator(_p + _size); }
    const_iterator end() const { return const_iterator(_p + _size); }
    reverse_iterator rbegin() { return reverse_iterator(_p); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(_p); }
    reverse_iterator rend() { return reverse_iterator(_p + _size); }
    const_reverse_iterator rend() const { return const_reverse_iterator(_p + _size); }
    
private:
    allocator_type &_alloc;
    size_type       _size;
    size_type       _capacity;
    pointeur        _p;

    //private fcts
    void    in_swap(iterator it1, iterator it2) {
        T temp = *it1;
        *it1 = *it2;
        *it2 = temp;
    }


};
}
#endif