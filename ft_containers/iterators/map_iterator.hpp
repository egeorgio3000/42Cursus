#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

namespace ft {

template <typename T, class Allocator>
struct AVLtree {
    
    Allocator alloc;
    T   data;
    AVLtree *right;
    AVLtree *left;
    AVLtree *parent;
    size_t  height;
    AVLtree(T value = T(), AVLtree *_parent = NULL) : right(NULL), left(NULL), parent(_parent), height(0), alloc(Allocator()) {
        alloc.construct(&data, value);
    }
    //bool leaf() { return !right && !left ? true : false; }
};

template <typename T>
class map_iterator {};

}
#endif