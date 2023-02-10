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

template <typename Key, typename T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T>>>
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
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
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
    explicit myMap() : _alloc(Allocator()), _nodeAlloc(), _size(0), _root(NULL) {}

    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare &comp = Compare(), const allocator_type & = Allocator()) {}

    map(const ft::map<key_type, mapped_type, key_compare, allocator_type> &src)
    {
        if (this != &src)
            *this = src;
    }

    // modifiers
    ft::pair<iterator, bool> insert(value_type const &value)
    {
        iterator it;
        Node *actual = insertNode(value);
        _root = balanceTree(actual);
        return ft::make_pair(it, true);
    }

protected:
    typedef typename ft::AVLtree<value_type, allocator_type> Node;
    typedef typename allocator_type::rebind<Node>::other node_allocator_type;

    //AVLtree functions
    Node *insertNode(value_type const &value)
    {
        if (_size == 0)
        {
            _root = _nodeAlloc.allocate(1);
            _nodeAlloc.construct(_root, Node(value));
            _size++;
            return _root;
        }
        Node *actual = _root;
        while (actual)
        {

            if (actual->data > value)
            {
                if (actual->left)
                    actual = actual->left;
                else
                    break;
            }
            else
            {
                if (actual->right)
                    actual = actual->right;
                else
                    break;
            }
        }
        if (actual->data > value)
        {
            actual->left = _nodeAlloc.allocate(1);
            _nodeAlloc.construct(actual->left, Node(value, actual));
            actual = actual->left;
        }
        else
        {
            actual->right = _nodeAlloc.allocate(1);
            _nodeAlloc.construct(actual->right, Node(value, actual));
            actual = actual->right;
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

    int ratioNode(Node *node)
    {
        return (node->height - (node->left != NULL ? node->left->height : -1)) - (node->height - (node->right != NULL ? node->right->height : -1));
    }

    void adjustHeight(Node *inserted)
    {
        inserted->height = 0;
        if (inserted->right)
            inserted->height = inserted->right->height + 1;
        if (inserted->left)
        {
            if (inserted->left->height >= inserted->height)
                inserted->height = inserted->left->height + 1;
        }
        inserted = inserted->parent;
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
        if (newRoot->parent)
        {
            newRoot->parent->right = oldRoot->parent;
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
        if (newRoot->parent)
        {
            newRoot->parent->left = oldRoot->parent;
        }
        oldRoot->parent = newRoot;
        adjustHeight(oldRoot);
        adjustHeight(newRoot);
        return newRoot;
    }

    Node *balanceTree(Node *inserted)
    {
        bool flag = false;
        Node *tmpInserted = inserted;
        do
        {
            // std::cout << ratioNode(inserted) << " = " << inserted->height << " - " << inserted->left->height << " - (" << inserted->height << " - (-1) )" << std::endl;
            inserted = inserted->parent;
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
                if (flag)
                {
                    break;
                }
            }
            else if (ratioNode(inserted) > 1)
            {
                if (inserted->left->right && inserted->left->right->height > 0)
                {
                    inserted->right = rotateRight(inserted->right);
                    inserted = rotateLeft(inserted);
                }
                else
                {
                    inserted = rotateLeft(inserted);
                }
                if (flag)
                    break;
            }
        } while (inserted != _root);

        return (inserted); // return le nouveau _root
    }

private:
    Node *_root;
    Node *_leaf;
    size_type _size;
    allocator_type _alloc;
    node_allocator_type _nodeAlloc;
    key_compare _comp;
};
}

#endif