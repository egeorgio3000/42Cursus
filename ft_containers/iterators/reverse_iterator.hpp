#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
template<typename Iter>
class reverse_iterator {
    public:
    typedef typename ft::iterator_traits<Iter>::value_type value_type;
    typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
    typedef typename ft::iterator_traits<Iter>::pointer pointer;
    typedef typename ft::iterator_traits<Iter>::reference reference;
    typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;

    reverse_iterator() : _it() {}
    reverse_iterator( reverse_iterator<Iter> const &it ) : _it(it) {}
    template <typename U>
    reverse_iterator(const reverse_iterator<U> &other) : _it(other.base()) {};

    ~reverse_iterator() {};

    Iter base() const { return _it; }

    //operators
    template <typename U>
    reverse_iterator &operator=(reverse_iterator<U> const &other) { 
        _it(other);
        return (*this);
    }
        //comparaison
    template <class U>
    bool	operator==(const reverse_iterator<U> &rhs) const { return _it == rhs.base(); };

    template <class U>
    bool	operator!=(const reverse_iterator<U> &rhs) const { return _it != rhs.base(); };

    template <class U>
    bool	operator<(const reverse_iterator<U> &rhs) const { return _it > rhs.base(); };

    template <class U>
    bool	operator>(const reverse_iterator<U> &rhs) const { return _it < rhs.base(); };

    template <class U>
    bool	operator<=(const reverse_iterator<U> &rhs) const { return _it >= rhs.base(); };

    template <class U>
    bool	operator>=(const reverse_iterator<U> &rhs) const { return _it <= rhs.base(); };

        //dereference
    
    reference operator*() {
        Iter tmp = _it;
        return (*--tmp);
    }
    pointer operator->() {
        Iter tmp = _it;
        return &(*--tmp);
    }

    reference operator[]( const std::size_t n ) {return *(*this + n); }

        //increment
    reverse_iterator& operator++() {
        --_it;
        return (*this);
    }

    reverse_iterator operator++(int) {
        reverse_iterator tmp(*this);
        _it--;
        return (tmp);
    }

    reverse_iterator operator--(int) {
        reverse_iterator tmp(*this);
        _it++;
        return (tmp);
    }

    reverse_iterator& operator--() {
        ++_it;
        return (*this);
    }

    reverse_iterator& operator+=( difference_type n ) {
        _it -= n;
        return (*this);
    }

    reverse_iterator& operator-=( difference_type n ) {
        _it += n;
        return (*this);
    }

    reverse_iterator operator+( difference_type n ) const {
        reverse_iterator tmp = *this;
        return tmp -= n;
    }

    reverse_iterator operator-( difference_type n ) const {
        reverse_operator tmp = *this;
        return tmp += n;
    }

    difference_type operator-(reverse_iterator it) const { return it.base() - _it; }
    
        //arithmetic
    private:
    Iter _it;

};
}

#endif