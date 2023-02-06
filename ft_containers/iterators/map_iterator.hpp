#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

namespace ft {

template <typename T>
struct AVLtree {
    
    T   data;
    AVLtree *right;
    AVLtree *left;
    AVLtree *parent;
    size_t  height;
    AVLtree() : data(), right(NULL), left(NULL), parent(NULL), depth(0) {}
};

template <typename T>
class map_iterator {};

}
#endif