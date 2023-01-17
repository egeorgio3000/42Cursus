#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <iostream>

namespace ft {

template<class Iter>
struct iterator_traits {
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;
    typedef typename Iter::iterator_category iterator_category;
};

template<typename T>
struct iterator_traits<T*> {
    typedef typename std::ptrdiff_t difference_type;
    typedef typename T value_type;
    typedef typename T* pointer;
    typedef typename T& reference;
    typedef typename std::random_access_iterator_tag iterator_category;
};

template<typename T>
struct iterator_traits<const T*> {
    typedef typename std::ptrdiff_t difference_type;
    typedef typename T value_type;
    typedef typename const T* pointer;
    typedef typename const T& reference;
    typedef typename std::random_access_iterator_tag iterator_category;
};

}
#endif