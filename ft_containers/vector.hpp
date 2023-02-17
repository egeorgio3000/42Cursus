#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <string>
#include "./iterators/vector_iterator.hpp"
#include "./iterators/reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "algorithm.hpp"

namespace ft {
    
template<typename T, class Allocator = std::allocator<T> >
class vector {
public:
    //  types:
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    typedef T value_type;
    typedef vector_iterator<value_type> iterator; 
    typedef vector_iterator<const value_type> const_iterator; 
    typedef std::size_t size_type; 
    typedef std::ptrdiff_t difference_type;
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
            _alloc.construct(_p + i, value);
        }

    }
    
    template <typename InputIterator>
    vector(InputIterator first,  typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type &allocator = Allocator()) : _alloc(allocator), _size(0), _capacity(0), _p(NULL) {
        InputIterator it = first;
        for(; it != last; it++)
            this->push_back(*it);
        _capacity = last - first;
    }
    
    vector(ft::vector<T, allocator_type> const& src) : _alloc(src.get_allocator()), _size(0), _capacity(0), _p(NULL)  {
        if (this != &src)
            *this = src;
    }
    ~vector() { _alloc.deallocate(_p, _capacity); }

    //operators
    ft::vector<T, allocator_type> &operator=(ft::vector<T, allocator_type> const &rhs) {
        clear();
        for (const_iterator it = rhs.begin(); it != rhs.end(); it++)
            this->push_back(*it);
        /*_alloc.deallocate(_p, _capacity);
        _p = _alloc.allocate(rhs.size());
        _size = rhs.size();
        if (_capacity < rhs.capacity())
            _capacity = rhs.capacity();
        for (size_type i = 0; i < rhs.size(); i++)
            _alloc.construct(_p + i, rhs[i]);*/
        return (*this);
    }

    //setters
    template <class InputIterator>
    void assign(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
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

    void clear() {
        for (size_type i = 0; i < size(); i++) {
            _alloc.destroy(_p + i);
        }
        _size = 0;
        //_p = NULL;
    }

    iterator insert(iterator position, const T& x) {
        size_type pos = position - _p;
        if (!_size) {
            push_back(x);
            return (end());
        }
        if (_size + 1 > _capacity)
            reserve(_capacity * 2);
        pointer ptrPos = _p + pos;
        pointer ptrEnd = _p + _size;
        for (; ptrEnd != ptrPos; ptrEnd--) {
            _alloc.construct(ptrEnd, *(ptrEnd - 1));
            _alloc.destroy(ptrEnd - 1);
        }
        _alloc.construct(ptrPos, x);
        _size++;
        return (iterator(_p + pos));
    }

    iterator insert(iterator position, size_type n, const T& x) {
        size_type pos = (position - _p);
        if (n && 2 * _size < n + _size) {
            reserve(n + _size);
            position = iterator(_p + pos);
        }
        else if (n && _size + n > _capacity) {
            reserve(_size * 2);
            position = iterator(_p + pos);
        }
        pointer ptrPos = _p + pos;
        pointer ptrEnd = _p + (_size + n -1);
        for (; ptrEnd != ptrPos + n - 1; --ptrEnd) {
            _alloc.construct(ptrEnd, *(ptrEnd - n));
            _alloc.destroy(ptrEnd - n);
        }
        for (size_type i = 0; i < n; i++) {
            _alloc.construct(ptrPos + i, x);
        }
        _size += n;
        return (iterator(_p + pos));
    }

    template <class InputIterator>
    iterator insert(iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
        size_type n = last - first;
        size_type pos = (position - _p);
        if (n && 2 * _size < n + _size) {
            reserve(n + _size);
            position = iterator(_p + pos);
        }
        else if (n && _size + n > _capacity) {
            reserve(_size * 2);
            position = iterator(_p + pos);
        }
        pointer ptrPos = _p + pos;
        pointer ptrEnd = _p + (_size + n -1);
        for (; ptrEnd != ptrPos + n - 1; --ptrEnd) {
            _alloc.construct(ptrEnd, *(ptrEnd - n));
            _alloc.destroy(ptrEnd - n);
        }
        for (size_type i = 0; i < n; i++) {
            _alloc.construct(ptrPos + i, *first);
            first++;
        }
        _size += n;
        return (iterator(_p + pos));
    }

    iterator erase( iterator pos ) {
        size_type position = (pos - _p);
        _alloc.destroy(_p + position);
        _size--;
        for (size_type i = position; i < _size; i++) {
            _alloc.construct(_p + i, *(_p + i + 1));
            _alloc.destroy(_p + i + 1);
        }
        return (iterator(_p + position) );
    }

    iterator erase( iterator first, iterator last) {
        difference_type lengh = last - first;
        size_type start = (first - _p);
        size_type end = last - _p;
        for (size_type i = start; i < end; i++) {
            _alloc.destroy(_p + i) ;
            _size--;
        }
        for (size_type i = start; i < _size; i++) {
            _alloc.construct(_p + i, *(_p + i + lengh));
            _alloc.destroy(_p + i + lengh);
        }
        return (iterator(_p + start));
    }

    void push_back(const T&value) {
        if ( _size + 1 > _capacity ) {
            if (!_capacity)
                reserve(1);
            else {
                reserve(_capacity * 2);
            }
        }
        _alloc.construct(&(*this->end()), value);
        _size += 1;
    
    }

    void pop_back() { 
        if (_size) {
            _size--;
            _alloc.destroy(_p + _size);
        }
    }

    void resize(size_type count, T const &value = T()) {
        if (_size >= count) {
            for (size_type i = count; i < _size; i++) {
                _alloc.destroy(_p + i);
            }
        }
        else {
            reserve(count);
            for (size_type i = _size; i < count; i++) {
                _alloc.construct(_p + i, value);
            }
        }
        _size = count;
    }

    void swap(vector &other) {
        if (this != &other) {
            ft::swap(_p, other._p);
            ft::swap(_size, other._size);
            ft::swap(_capacity, other._capacity);
        }
    }

        //capacity
    size_type max_size() const { return _alloc.max_size(); }
    bool empty() const { return(_size ? false : true); }
    size_type size() const { return _size; }
    size_type capacity() const { return _capacity; }

    void reserve( size_type new_cap ) {
        if ( new_cap > max_size() ) { throw std::length_error("vector::reserve"); }
        if ( new_cap > _capacity ) {
            pointer new_p = _alloc.allocate( new_cap );
            for (size_type i = 0; i < _size; i++) {
                _alloc.construct(new_p + i, *(_p + i));
                _alloc.destroy(_p + i);

            }
            _alloc.deallocate(_p, _capacity);
            _p = new_p;
            _capacity = new_cap;
        } 
    }

        // Element access
    reference at(size_type pos) {
        if (pos >= size())
            throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(pos) + ") >= this->size() (which is " + ft::to_string(_size) + ")");
        return (*(_p + pos));
    }

    const_reference at(size_type pos) const {
        if (pos >= size())
            throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(pos) + ") >= this->size() (which is " + ft::to_string(_size) + ")");
        return (*(_p + pos));
    }

    reference operator[]( size_type pos ) { return *(_p + pos); }
    const_reference operator[]( size_type pos ) const { return *(_p + pos); }

    reference front() { return *_p; }
    const_reference front() const { return *_p; }

    reference back() { return *(_p + _size - 1); }
    const_reference back() const { return *(_p + _size - 1); }

    pointer data() { return (_size ? _p : NULL); }
    const_pointer data() const { return (_size ? _p : NULL); }


        // iterators:
    iterator begin()  { return iterator(_p); }
    const_iterator begin() const { return const_iterator(_p); }
    iterator end() { return iterator(_p + _size); }
    const_iterator end() const { return const_iterator(_p + _size); }
    reverse_iterator rbegin() { return reverse_iterator(this->end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
    reverse_iterator rend() { return reverse_iterator(this->begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }
    
private:
    allocator_type _alloc;
    size_type       _size;
    size_type       _capacity;
    pointer        _p;


};
// non member functions

template< class T, class Alloc >
bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) { return equal(lhs.begin(), lhs.end(), rhs.begin()); }
template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) { return !equal(lhs.begin(), lhs.end(), rhs.begin()); }
template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) { return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || equal(lhs.begin(), lhs.end(), rhs.begin()); }
template< class T, class Alloc >
bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) { return !lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || equal(lhs.begin(), lhs.end(), rhs.begin()); }
template< class T, class Alloc >
bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) { return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
template< class T, class Alloc >
bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) { return !lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

template< class T, class Alloc >
void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) { lhs.swap(rhs); }
}
#endif