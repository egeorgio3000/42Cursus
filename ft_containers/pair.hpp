#ifndef PAIR_HPP
# define PAIR_HPP

#include "algorithm.hpp"
namespace ft {

template <typename T1, typename T2>
struct pair {
   
    // types:
    typedef T1 first_type;
    typedef T2 second_type;

    //member attributs
    first_type first;
    second_type second;

    // constructors/destructor
    pair() : first(), second() {}

    pair( const first_type& x, const second_type& y ) : first(x), second(y) {}

    pair(const pair& p)
        : first(p.first), second(p.second) { }

    template< class U1, class U2 >
        pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}

    //operator
    pair& operator=( const pair& other ) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return (*this);
    }

};

// non-member functions
template< class T1, class T2 >
ft::pair<T1, T2> make_pair( T1 t, T2 u ) { return pair<T1, T2>(t, u); }

template< class T1, class T2 >
bool operator==( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) { return (lhs.first == rhs.first && lhs.second == rhs.second); }
template< class T1, class T2 >
bool operator!=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) { return (lhs.first != rhs.first || lhs.second != rhs.second); }
template< class T1, class T2 >
bool operator<=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) { return lhs.first <= rhs.first ? lhs.second <= rhs.second : false;}
template< class T1, class T2 >
bool operator>=( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) { return lhs.first >= rhs.first ? lhs.second >= rhs.second : false; }
template< class T1, class T2 >
bool operator<( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) { return lhs.first <= rhs.first ? lhs.second < rhs.second : false; }
template< class T1, class T2 >
bool operator>( const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) { return lhs.first >= rhs.first ? lhs.second > rhs.second : false; }
}
#endif