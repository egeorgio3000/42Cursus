#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

#include <sstream>
#include <string>

namespace ft {
    
template <typename T>
std::string to_string(T Number) {
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 ) {
    for (; first1 != last1; first1++) {
        if (*first1 != *first2)
            return 0;
        first2++;
    }
    return 1;
}

template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p ) {
    for (; first1 != last1; first1++) {
        if (!p(*first1,  *first2))
            return 0;
        first2++;
    }
    return 1;
}

template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 ) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2)
            return 1;
        else if (*first1 > *first2)
            return 0;
        first1++;
        first2++;
    }
    return (first1 == last1) && (first2 != last2);
}

template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp ) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first1, *first2))
            return 1;
        else if (comp(*first2, *first1))
            return 0;
        first1++;
        first2++;
    }
    return (first1 == last1) && (first2 != last2);
}

template< class T >
void swap( T& a, T& b ) {
    T tmp = a;
    a = b;
    b = tmp;
}
}

#endif