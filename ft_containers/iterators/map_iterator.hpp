#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "iterator_traits.hpp"
namespace ft {

template <typename T>
struct AVLtree {
    
    T   data;
    AVLtree *right;
    AVLtree *left;
    AVLtree *parent;
    size_t  height;
    AVLtree(AVLtree *_parent = NULL) : data(), right(NULL), left(NULL), parent(_parent), height(0) {}
    //bool leaf() { return !right && !left ? true : false; }
};

template <typename T>
class map_iterator {
public:
    typedef typename ft::iterator_traits<T*>::value_type value_type;
    typedef typename ft::iterator_traits<T*>::difference_type difference_type;
    typedef typename ft::iterator_traits<T*>::pointer pointer;
    typedef typename ft::iterator_traits<T*>::reference reference;
    typedef typename ft::iterator_traits<T*>::iterator_category iterator_category;

    typedef AVLtree<value_type> Node;

    map_iterator() : _node(NULL) {}
    map_iterator( map_iterator<value_type> const &it ) : _node(it.getNode()) {}
    map_iterator( pointer p ) : _node(p) {}
    map_iterator( reference p ) : _node(&p) {}
    ~map_iterator() {}

    //operators
    map_iterator<value_type> &operator=(map_iterator<value_type> const &it) { 
        _node = it.getNode();
        return (*this);
    }

    //dereference
    
    reference operator*() const { return _node->data; }
    pointer operator->() const { return &_node->data; }
    //reference operator[]( const std::size_t n ) {return *(_p + n); }

    //increment
    map_iterator &operator++() {
        if(_node->right) {
            _node = _node->right;
            while (_node->left)
                _node = _node->left;
        } else {
            while (_node->parent && _node == _node->parent->right)
                _node = _node->parent;
        }
    }

    map_iterator &operator++(int) {
        map_iterator tmp(*this);
        (*this)++;
        return tmp;
    }

    map_iterator &operator--() {
        if(_node->left) {
            _node = _node->left;
            while (_node->right)
                _node = _node->right;
        } else {
            while (_node->parent && _node == _node->parent->left)
                _node = _node->parent;
        }
    }

    map_iterator &operator--(int) {
        map_iterator tmp(*this);
        (*this)--;
        return tmp;
    }

    Node *getNode() const { return _node; }

    bool operator==(const map_iterator& it) const { return _node == it.getNode(); }
    bool operator!=(const map_iterator& it) const { return _node != it.getNode(); }
private:
    
    Node *_node;
};

}
#endif