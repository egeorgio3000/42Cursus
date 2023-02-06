#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <string>

template <typename T>
struct AVLtree {
    
    T   data;
    AVLtree *right;
    AVLtree *left;
    //AVLtree *parent;
    size_t  height;
    AVLtree(T value = T()) : data(value), right(NULL), left(NULL), height(0) {}
    bool leaf() { return !right && !left ? true : false; }
};

template <typename T, class Allocator = std::allocator<T> >
class myMap {
    public:
        //typedefs
        typedef T value_type;
        typedef AVLtree<value_type> Node;
        typedef Allocator allocator_type;
        typedef typename allocator_type::template rebind<Node>::other node_allocator_type;
        typedef std::size_t size_type;

        //attributes
        Node *_root;
        //Node *_leaf;
        size_type _size;
        allocator_type _alloc;
        node_allocator_type _nodeAlloc;

        explicit myMap() : _alloc(Allocator()), _nodeAlloc(), _size(0), _root(NULL) {
        /*_root = _nodeAlloc.allocate(1);
        _alloc.construct(_root, Node());
        _leaf = _nodeAlloc.allocate(1);
        _leaf.construct(_leaf, Node());
        _root->right = _leaf;
        _leaf->parent = _root; */
        }
        ~myMap() { _nodeAlloc.deallocate(_root, 1); }

        //insert
        Node *insert(value_type const &value) {
            if (_size == 0) {
                _root = _nodeAlloc.allocate(1);
                _nodeAlloc.construct(_root, Node(value));
                _size++;
                return _root;
            }
            Node *actual = _root;
            while (actual) {
                
                if (actual->data > value) {
                    if (!actual->right)
                        actual->height++;
                    if (actual->left)
                        actual = actual->left;
                    else
                        break;
                }
                else {
                    if (!actual->left)
                        actual->height++;
                    if (actual->right)
                        actual = actual->right;
                    else
                        break;
                }
            }
            if (actual->data > value) {
                actual->left = _nodeAlloc.allocate(1);
                _nodeAlloc.construct(actual->left, Node(value));
                actual = actual->left;
            }
            else {
                actual->right = _nodeAlloc.allocate(1);
                _nodeAlloc.construct(actual->right, Node(value));
                actual = actual->right;
            }
            _size++;
            return actual;
        }
    
};

int main() {
    myMap<int> tree;
    tree.insert(5);
    std::cout << "root : height: " << tree._root->height << "_size : " << tree._size << " value : " << tree._root->data << std::endl;
    tree.insert(3);
    std::cout << "root : height: " << tree._root->height << "_size : " << tree._size << " value : " << tree._root->data << std::endl;
    std::cout << "->left: height: " << tree._root->left->height << "_size : " << tree._size << " value : " << tree._root->left->data << std::endl;
    tree.insert(4);
    std::cout << "root : height: " << tree._root->height << "_size : " << tree._size << " value : " << tree._root->data << std::endl;
    std::cout << "->left: height: " << tree._root->left->height << "_size : " << tree._size << " value : " << tree._root->left->data << std::endl;
    std::cout << "->left->right: height: " << tree._root->left->right->height << "_size : " << tree._size << " value : " << tree._root->left->right->data << std::endl;
    tree.insert(8);
    std::cout << "root : height: " << tree._root->height << "_size : " << tree._size << " value : " << tree._root->data << std::endl;
    std::cout << "->left: height: " << tree._root->left->height << "_size : " << tree._size << " value : " << tree._root->left->data << std::endl;
    std::cout << "->left->right: height: " << tree._root->left->right->height << "_size : " << tree._size << " value : " << tree._root->left->right->data << std::endl;
    std::cout << "->right: height: " << tree._root->right->height << "_size : " << tree._size << " value : " << tree._root->right->data << std::endl;

}