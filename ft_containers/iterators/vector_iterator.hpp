#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

template<typename T>
class vector_iterator {
public:
    typedef typename ft::iterator_traits<T*>::value_type value_type;
    typedef typename ft::iterator_traits<T*>::difference_type difference_type;
    typedef typename ft::iterator_traits<T*>::pointer pointer;
    typedef typename ft::iterator_traits<T*>::reference reference;
    typedef typename ft::iterator_traits<T*>::iterator_category iterator_category;

    vector_iterator() : _p(NULL) {}
    vector_iterator( vector_iterator<value_type> const &it ) : _p(&(*it)) {}
    vector_iterator( pointer p ) : _p(p) {}
    vector_iterator( reference p ) : _p(&p) {}
    ~vector_iterator() {}

    //operators
    vector_iterator &operator=(const vector_iterator<T> &it) {
        if (this != &it)
            _p = &(*it);
        return (*this);
    }
        //comparaison
    bool operator==(vector_iterator<value_type> const &it) const { return (_p == &(*it) ? true : false); }
    bool operator==(vector_iterator<const value_type> const &it) const { return (_p == &(*it) ? true : false); }
    bool operator!=(vector_iterator<value_type> const &it) const { return (_p != &(*it) ? true : false); }
    bool operator!=(vector_iterator<const value_type> const &it) const { return (_p != &(*it) ? true : false); }
    bool operator>=(vector_iterator<value_type> const &it) const { return (_p >= &(*it) ? true : false); }
    bool operator>=(vector_iterator<const value_type> const &it) const { return (_p >= &(*it) ? true : false); }
    bool operator<=(vector_iterator<value_type> const &it) const { return (_p <= &(*it) ? true : false); }
    bool operator<=(vector_iterator<const value_type> const &it) const { return (_p <= &(*it) ? true : false); }
    bool operator>(vector_iterator<value_type> const &it) const { return (_p > &(*it) ? true : false); }
    bool operator>(vector_iterator<const value_type> const &it) const { return (_p > &(*it) ? true : false); }
    bool operator<(vector_iterator<value_type> const &it) const { return (_p < &(*it) ? true : false); }
    bool operator<(vector_iterator<const value_type> const &it) const { return (_p < &(*it) ? true : false); }

        //dereference
    
    reference operator*() const { return *_p; }
    pointer operator->() const { return _p; }
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
        vector_iterator tmp = *this;
        return tmp += n;
    }

    friend vector_iterator operator+(difference_type n, vector_iterator& other) { return (vector_iterator(n + other._p)); }

    vector_iterator operator-( const int n ) const {
        vector_iterator tmp = *this;
        return tmp -= n;
    }

    difference_type operator-(vector_iterator const &it) const { return _p - &(*it); }
        //arithmetic
    



private:
    pointer _p;

};

}
/*namespace ft {
template <class T>
class vector_iterator {
private:

    T* _current;

public:

    typedef typename iterator_traits<T*>::difference_type difference_type;
    typedef typename iterator_traits<T*>::value_type value_type;
    typedef typename iterator_traits<T*>::pointer pointer;
    typedef typename iterator_traits<T*>::reference reference;
    typedef typename iterator_traits<T*>::iterator_category iterator_category;


    vector_iterator()
        : _current(NULL) { }

    vector_iterator(const vector_iterator<value_type>& other)
        : _current(&(*other)) { }

    vector_iterator(pointer ptr)
        : _current(ptr) { }

    vector_iterator(const reference ref) { _current = &ref; }

    ~vector_iterator() { }

    vector_iterator& operator=(const vector_iterator<T>& other) {
        if (this != &other)
            _current = &(*other);
        return (*this);
    }


    bool operator==(const vector_iterator<T>& other) { return (_current == &(*other)); }
    bool operator==(const vector_iterator<const T>& other) const { return (_current == &(*other)); }
    bool operator!=(const vector_iterator<T>& other) { return (_current != &(*other)); }
    bool operator!=(const vector_iterator<const T>& other) const { return (_current != &(*other)); }
    bool operator>=(const vector_iterator<T>& other) { return (_current >= &(*other)); }
    bool operator>=(const vector_iterator<const T>& other) const { return (_current >= &(*other)); }
    bool operator<=(const vector_iterator<T>& other) { return (_current <= &(*other)); }
    bool operator<=(const vector_iterator<const T>& other) const { return (_current <= &(*other)); }
    bool operator>(const vector_iterator<T>& other) { return (_current > &(*other)); }
    bool operator>(const vector_iterator<const T>& other) const { return (_current > &(*other)); }
    bool operator<(const vector_iterator<T>& other) { return (_current < &(*other)); }
    bool operator<(const vector_iterator<const T>& other) const { return (_current < &(*other)); }

    reference operator*() const { return (*_current); }

    pointer operator->() const { return (_current); }

    reference operator[](const std::size_t n) { return (*(_current + n)); }


    vector_iterator operator+(difference_type n) const { return (vector_iterator(_current + n)); }

    difference_type operator+(const vector_iterator& other) const {
        return (reinterpret_cast<long>(_current)
            + reinterpret_cast<long>(&(*other)));
    }

    vector_iterator& operator+=(const int n) {
        _current += n;
        return (*this);
    }

    friend vector_iterator operator+(difference_type n, vector_iterator& other) { return (vector_iterator(n + other._current)); }

    vector_iterator operator-(const int n) const { return (vector_iterator(_current - n)); }

    difference_type operator-(const vector_iterator& other) const { return (_current - &(*other)); }

    vector_iterator& operator-=(const int n) {
        _current -= n;
        return (*this);
    }

    friend vector_iterator operator-(difference_type n, vector_iterator& other) { return (vector_iterator(n - other._current)); }


    vector_iterator& operator++() {
        ++_current;
        return (*this);
    }

    vector_iterator operator++(int) {
        vector_iterator tmp(*this);
        _current++;
        return (tmp);
    }

    vector_iterator operator--(int) {
        vector_iterator tmp(*this);
        _current--;
        return (tmp);
    }

    vector_iterator& operator--() {
        --_current;
        return (*this);
    }
}; 
}
*/

#endif