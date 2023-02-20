#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <stdexcept>
#include <memory>
#include <string>
#include "./iterators/map_iterator.hpp"
#include "./iterators/reverse_iterator.hpp"
#include "pair.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

namespace ft
{

template <typename Key, typename T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
public:
    // types:
    typedef Key key_type;
    typedef T mapped_type;
    typedef typename ft::pair<const key_type, mapped_type> value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef map_iterator<value_type> iterator;
    typedef map_iterator<const value_type> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    // class value_compare
    class value_compare : public std::binary_function<value_type, value_type, bool>
    {
        friend class map;

    protected:
        Compare comp;
        value_compare(Compare c) : comp(c) {}

    public:
        bool operator()(const value_type &x, const value_type &y) const { return comp(x.first, y.first); }
    };

    // constructors
    explicit map() : _root(NULL), _size(0), _alloc(Allocator()), _nodeAlloc() {
        _leaf = _nodeAlloc.allocate(1);
        _nodeAlloc.construct(_leaf, Node());
    }

    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare &comp = Compare(), const allocator_type &alloc = Allocator()) : _comp(comp), _alloc(alloc), _nodeAlloc(), _size(0), _root(NULL), _leaf(NULL) {
        _leaf = _nodeAlloc.allocate(1);
        _nodeAlloc.construct(_leaf, Node());
        insert(first, last);
    }

    map(const ft::map<key_type, mapped_type, key_compare, allocator_type> &src)
    {
        if (this != &src)
            *this = src;
    }

    ~map() {
        clear();
        _nodeAlloc.destroy(_leaf);
        _nodeAlloc.deallocate(_leaf, 1);
    }

    map &operator=( map const &rhs ) {
        if (this != &rhs) {
            clear();
            _alloc = rhs._alloc;
            _nodeAlloc = rhs._nodeAlloc;
            _comp = rhs._comp;
            _leaf = _nodeAlloc.allocate(1);
            _nodeAlloc.construct(_leaf, Node());
            _size = 0;
            insert(rhs.begin(), rhs.end());
        }
        return *this;
    }

    allocator_type get_allocator() const { return _alloc; }

    // modifiers
    ft::pair<iterator, bool> insert(value_type const &value)
    {
        iterator checkDuplicate = find(value.first);
        if (checkDuplicate != end())
            return (ft::make_pair<iterator, bool>(checkDuplicate, false));
        if (_size == max_size()) {
            return (ft::make_pair<iterator, bool>(lower_bound(value.first), false));
        }
        Node *node = insertNode(value);
        _root = balanceTree(node);
        return ft::make_pair(iterator(node), true);
    }

    iterator insert( iterator pos, const value_type& value ) {
        ( void ) pos;
        return insert(value).first;
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        ft::pair<iterator, bool> pairNode;
        while (first != last) {
            pairNode = insert(*first);
            if (!pairNode.second)
                break;
            first++;
        }
    }

    iterator erase (iterator pos ) {
        iterator ret = pos;
        ret++;
        Node *node = deleteNode(pos.getNode());
        _root = balanceTree(node);
        return (ret);
    }

    iterator erase( iterator first, iterator last ) {
        iterator ret = last;
        ret++;
        while (first != last) {
            first = erase(first);
        }
        return (first);
    }

    size_type erase( const Key& key ) {
        iterator pos = find(key);
        if (pos == end())
            return 0;
        erase(pos);
        return 1;
    }

    void clear() {
        while (_size)
            deleteNode(_root);
    }

    void swap(map& other) {
        ft::swap(_root, other._root);
        ft::swap(_leaf, other._leaf);
        ft::swap(_size, other._size);
        ft::swap(_comp, other._comp);
        ft::swap(_nodeAlloc, other._nodeAlloc);
        ft::swap(_alloc, other._alloc);
    }
    // iterators

    iterator begin() {
        Node *node = _root;
        if (!_size)
            return (iterator(_leaf));
        while (node->left)
            node = node->left;
        return iterator(node);
    }

    const_iterator begin() const {
        Node *node = _root;
        if (!_size)
            return (const_iterator(_leaf));
        while (node->left)
            node = node->left;
        return const_iterator(node);
    }

    reverse_iterator rbegin(void) { return reverse_iterator(end()); }
    const_reverse_iterator rbegin(void) const { return const_reverse_iterator(end()); }

    iterator end(void) { return iterator(_leaf); }
    const_iterator end(void) const { return const_iterator(_leaf); }

    reverse_iterator rend(void) { return reverse_iterator(begin()); }
    const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }

    //accesseurs

    reference at( const key_type &key ) {
        iterator it = find(key);
        if ( it == end() )
            throw std::out_of_range("ft::map::at");
        return (it->second);
    }

    const_reference at( const key_type &key) const {
        const_iterator it = find(key);
        if ( it == end() )
            throw std::out_of_range("ft::map::at");
        return (it->second);
    }

    reference operator[](const key_type &key) { return insertNode(ft::make_pair<key_type, mapped_type>(key, T()))->data.second; }

    //Capacity

    size_type size() const { return _size; }
    size_type max_size() const { return _nodeAlloc.max_size(); }
    bool      empty() const {return !_size; }

    //Look_up 

    size_type count( const Key& key ) const { return find(key) == end() ? 0 : 1; }
    iterator find( const Key& key ) { return iterator(findNode(key)); }
    const_iterator find( const Key& key ) const { return const_iterator(findNode(key)); }
    ft::pair<iterator, iterator> equal_range(const Key& key) { return ft::make_pair(lower_bound(key), upper_bound(key)); }
    ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const { return ft::make_pair(lower_bound(key), upper_bound(key)); }

    iterator lower_bound(const Key& key) {
        iterator it = begin();
        while (it != end() && _comp(it->first, key))
            it++;
        return it;
    }

    const_iterator lower_bound(const Key& key) const {
        const_iterator it = begin();
        while (it != end() && _comp(it->first, key))
            it++;
        return it;
    }

    iterator upper_bound(const Key& key) {
        iterator it = begin();
        while (it != end() && !_comp(key, it->first))
            it++;
        return it;
    }

    const_iterator upper_bound(const Key& key) const {
        const_iterator it = begin();
        while (it != end() && !_comp(key, it->first))
            it++;
        return it;
    }


    //observers 
    key_compare key_comp() const { return _comp; }
    value_compare value_comp() const { return value_compare(_comp); }


protected:
    typedef typename ft::AVLtree<value_type> Node;
    typedef typename allocator_type::template rebind<Node>::other node_allocator_type;

    //AVLtree functions

    Node *findNode(key_type const &key) {
        if (empty()) {
            return (_leaf);
        }
        Node *toFind = _root;
        while (toFind->data.first != key) {
            if (_comp(toFind->data.first, key)) {
                if (toFind->right && toFind->right != _leaf)
                    toFind = toFind->right;
                else
                    return _leaf;
            }
            else {
                if (toFind->left)
                    toFind = toFind->left;
                else
                    return _leaf;
            }
        }
        return toFind;
    }

    Node *insertNode(value_type const &value)
    {
        if (_size == 0)
        {
            
            _root = _nodeAlloc.allocate(1);
            _nodeAlloc.construct(_root, Node());
            _alloc.construct(&_root->data, value);
            _root->right = _leaf;
            _leaf->parent = _root;
            _size++;
            return _root;
        }
        Node *actual = _root;
        while (actual)
        {

            if (!_comp(actual->data.first, value.first))
            {
                if (actual->left)
                    actual = actual->left;
                else
                    break;
            }
            else
            {
                if (actual->right && actual->right != _leaf) {
                    actual = actual->right;
                }
                else
                    break;
            }
        }
        if (!_comp(actual->data.first, value.first))
        {
            actual->left = _nodeAlloc.allocate(1);
            _nodeAlloc.construct(actual->left, Node(actual));
            _alloc.construct(&actual->left->data, value);
            actual = actual->left;
        }
        else
        {
            bool flag = false;
            if (actual->right == _leaf) {
                flag = true;
            }
            actual->right = _nodeAlloc.allocate(1);
            _nodeAlloc.construct(actual->right, Node(actual));
            _alloc.construct(&actual->right->data, value);
            actual = actual->right;
            if (flag) { // reconnexion de la _leaf
                actual->right = _leaf;
                _leaf->parent = actual;
            }
        }
        Node *tmp = actual;
        while (tmp != NULL)
        {
            adjustHeight(tmp);
            tmp = tmp->parent;
        }
        _size++;

        return actual;
    }


    Node *deleteNode(Node *node) {
        if (!node || node == _leaf) {
            return _root;
        }
        //_alloc.destroy(node->data);
        Node *tmpNode = node;
        if (!node->left) {
            if (node != _root && node->parent->right == node) { //connexion du parent avec l'enfant
                node->parent->right = node->right;
            }
            else if ( node != _root && node->parent->left == node) 
                node->parent->left = node->right;
            if (node->right)
                node->right->parent = node->parent; // connexion de l'enfant avec le parent
            if (tmpNode->right && tmpNode->right != _leaf)
                tmpNode = tmpNode->right;
            else
                tmpNode = tmpNode->parent;
        }
        else if (!node->right) {
            if (node != _root && node->parent->right == node) { //connexion du parent avec l'enfant
                node->parent->right = node->left;
            }
            else if (node != _root && node->parent->left == node) {
                node->parent->left = node->left;
            }
            if (node->left)
                node->left->parent = node->parent;
            node->left->parent = node->parent; // connexion de l'enfant avec le parent
            tmpNode = tmpNode->left;
        }
        else if (node->left && node->right) {
            node = node->left;
            while (node->right) {
                node = node->right;
            }
            _alloc.construct(&tmpNode->data, node->data);
            if (node->left) {
                node->parent->right = node->left;
                node->left->parent = node->parent;
                tmpNode = node->left;
            }
            else
                tmpNode = node->parent;
        }
        _alloc.destroy(&node->data);
    //    _alloc.deallocate(&node->data, 1);
        _nodeAlloc.destroy(node);
        _nodeAlloc.deallocate(node, 1);
        Node *tmp = tmpNode;
        while (tmp != NULL)
        {
            adjustHeight(tmp);
            tmp = tmp->parent;
        }
        _size--;
        if (!_size) {
            //_alloc.destroy(&_root->data);
            //_nodeAlloc.destroy(_root);
            //_nodeAlloc.deallocate(_root, 1);
            return (_leaf);
        }
        return (tmpNode);
    }

    int ratioNode(Node *node)
    {
        return (node->height - (node->left != NULL ? node->left->height : -1)) - (node->height - ((node->right != NULL && node->right != _leaf) ? node->right->height : -1));
    }

    void adjustHeight(Node *inserted)
    {
        inserted->height = 0;
        if (inserted->right && inserted->right != _leaf)
            inserted->height = inserted->right->height + 1;
        if (inserted->left)
        {
            if (inserted->left->height >= inserted->height)
                inserted->height = inserted->left->height + 1;
        }
    }

    Node *rotateRight(Node *oldRoot)
    {
        Node *newRoot = oldRoot->left;
        if (newRoot->right)
        {
            oldRoot->left = newRoot->right;
            newRoot->right->parent = oldRoot;
        }
        else
            oldRoot->left = NULL;
        newRoot->right = oldRoot;
        newRoot->parent = oldRoot->parent;
        if (oldRoot->parent)
        {
            if (oldRoot->parent->left == oldRoot)
                oldRoot->parent->left = newRoot;
            else
                oldRoot->parent->right = newRoot;
        }
        oldRoot->parent = newRoot;
        adjustHeight(oldRoot);
        adjustHeight(newRoot);
        return newRoot;
    }

    Node *rotateLeft(Node *oldRoot)
    {
        Node *newRoot = oldRoot->right;
        if (newRoot->left)
        {
            oldRoot->right = newRoot->left;
            newRoot->left->parent = oldRoot;
        }
        else
        {
            oldRoot->right = NULL;
        }
        newRoot->left = oldRoot;
        newRoot->parent = oldRoot->parent;
        if (oldRoot->parent)
        {
            if (oldRoot->parent->left == oldRoot)
                oldRoot->parent->left = newRoot;
            else
                oldRoot->parent->right = newRoot;
        }
        oldRoot->parent = newRoot;
        adjustHeight(oldRoot);
        adjustHeight(newRoot);
        return newRoot;
    }

    Node *balanceTree(Node *inserted)
    {
        bool flag = false;
        while (inserted)
        {
            // std::cout << ratioNode(inserted) << " = " << inserted->height << " - " << inserted->left->height << " - (" << inserted->height << " - (-1) )" << std::endl;
            if (inserted == _root)
                flag = true;
            if (ratioNode(inserted) < -1)
            {
                if (inserted->left->right && inserted->left->right->height > 0)
                {
                    inserted->left = rotateLeft(inserted->left);
                    inserted = rotateRight(inserted);
                }
                else
                {
                    inserted = rotateRight(inserted);
                }
                if (!flag) {
                    for (Node *tmp = inserted->parent; tmp != NULL; tmp = tmp->parent)
                        adjustHeight(tmp);
                }
            }
            else if (ratioNode(inserted) > 1)
            {
                if (inserted->right->left && inserted->right->left->height > 0)
                {
                    inserted->right = rotateRight(inserted->right);
                    inserted = rotateLeft(inserted);
                }
                else
                {
                    inserted = rotateLeft(inserted);
                }
                if (!flag) {
                    for (Node *tmp = inserted->parent; tmp != NULL; tmp = tmp->parent)
                        adjustHeight(tmp);
                }
            }
            if (flag)
                break ;
            inserted = inserted->parent;
        }
        return (inserted); // return le nouveau _root
    }
#ifdef DEBUG
public:
#else
private:
#endif
    Node *_root;
    Node *_leaf;
    size_type _size;
    allocator_type _alloc;
    node_allocator_type _nodeAlloc;
    key_compare _comp;
};

//non member functions;

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ) { 
    if (lhs.size() != rhs.size())
        return 0;
    return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ) { return !(lhs == rhs); }

template <class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template <class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return (!(lhs < rhs) && !(lhs == rhs)); }

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return (!(lhs > rhs)); }

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) { return (!(lhs < rhs)); }

template <class Key, class T, class Compare, class Alloc>
void swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs) { lhs.swap(rhs); }

}
#endif