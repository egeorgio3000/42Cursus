#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

template<typename T>
class vector_iterator {
    public:
    typename typedef ft::iterator_traits<T*>::value_type value_type;
    typename typedef ft::iterator_traits<T*>::difference_type difference_type;
    typename typedef ft::iterator_traits<T*>::pointer pointer;
    typename typedef ft::iterator_traits<T*>::reference reference;
    typename typedef ft::iterator_traits<T*>::iterator_category iterator_category;

    vector_iterator() : _p(NULL) {}
    vector_iterator( vector_iterator<value_type> const &it ) : _p(&(*it)) {}
    vector_iterator( pointer p ) : _p(p) {}
    vector_iterator( reference p ) : _p(&p) {}
    ~vector_iterator() {}

    //operators
    vector_iterator<value_type> &operator=(vector_iterator<value_type> const &it) { 
        _p(&(*it));
        return (*this);
    }
        //comparaison
    bool operator==(vector_iterator<value_type> const &it) const { return (_p == &(*it) ? true : false); }
    bool operator!=(vector_iterator<value_type> const &it) const { return (_p != &(*it) ? true : false); }
    bool operator>=(vector_iterator<value_type> const &it) const { return (_p >= &(*it) ? true : false); }
    bool operator<=(vector_iterator<value_type> const &it) const { return (_p <= &(*it) ? true : false); }
    bool operator>(vector_iterator<value_type> const &it) const { return (_p > &(*it) ? true : false); }
    bool operator<(vector_iterator<value_type> const &it) const { return (_p < &(*it) ? true : false); }

        //dereference
    
    reference operator*() { return *_p; }
    pointer operator->() { return _p; }
    reference operator[]( const std::size_t n ) {return *(_p + n); }

        //increment
    vector_iterator& operator++() {
        ++_p;
        return (*this);
    }

    vector_iterator operator++(int) {
        vector_iterator tmp(*this);
        _p++;
        return (tmp);
    }

    vector_iterator operator--(int) {
        vector_iterator tmp(*this);
        _p--;
        return (tmp);
    }

    vector_iterator& operator--() {
        --_p;
        return (*this);
    }

    vector_iterator& operator+=( const int n ) {
        _p += n;
        return (*this);
    }

    vector_iterator& operator-=( const int n ) {
        _p -= n;
        return (*this);
    }

    vector_iterator operator+( const int n ) const {
        vector_iterator<value_type> tmp = *this;
        return tmp += n;
    }

    vector_iterator operator-( const int n ) const {
        vector_iterator<value_type> tmp = *this;
        return tmp -= n;
    }

    difference_type operator-(vector_iterator<value_type> it) const { return _p - it._p; }
    
        //arithmetic
    private:
    pointer _p;

};

}

#endif