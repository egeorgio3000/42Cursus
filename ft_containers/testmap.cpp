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
    AVLtree *parent;
    size_t  height;
    AVLtree(T value = T(), AVLtree *_parent = NULL) : data(value), right(NULL), left(NULL), parent(_parent), height(0) {}
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

        explicit myMap() : _alloc(Allocator()), _nodeAlloc(), _size(0), _root(NULL) {}
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
                    if (actual->left)
                        actual = actual->left;
                    else
                        break;
                }
                else {
                    if (actual->right)
                        actual = actual->right;
                    else
                        break;
                }
            }
            if (actual->data > value) {
                actual->left = _nodeAlloc.allocate(1);
                _nodeAlloc.construct(actual->left, Node(value, actual));
                actual = actual->left;
            }
            else {
                actual->right = _nodeAlloc.allocate(1);
                _nodeAlloc.construct(actual->right, Node(value, actual));
                actual = actual->right;
            }
            Node *tmp = actual;
            while (tmp != NULL) {
                adjustHeight(tmp);
                tmp = tmp->parent;
            }
            _size++;

            return actual;
        }

        int ratioNode(Node *node) {
            return (node->height - (node->left != NULL ? node->left->height : -1)) - (node->height - (node->right != NULL ? node->right->height : -1));
        }

        void adjustHeight(Node *inserted) {
                inserted->height = 0;
                if (inserted->right)
                    inserted->height = inserted->right->height + 1;
                if (inserted->left) {
                    if (inserted->left->height >= inserted->height)
                        inserted->height = inserted->left->height + 1;
                }
                inserted = inserted->parent;
        }

        Node *rotateRight(Node *oldRoot) {
            Node *newRoot = oldRoot->left;
            if (newRoot->right) {
                oldRoot->left = newRoot->right;
                newRoot->right->parent = oldRoot;
            }
            else
                oldRoot->left = NULL;
            newRoot->right = oldRoot;     
            newRoot->parent = oldRoot->parent;   
            if (newRoot->parent) {
                newRoot->parent->right = oldRoot->parent;
            }   
            oldRoot->parent = newRoot;
            adjustHeight(oldRoot);
            adjustHeight(newRoot);
            return newRoot;

        }

        Node *rotateLeft(Node *oldRoot) {
            Node *newRoot = oldRoot->right;
            if (newRoot->left) {
                oldRoot->right = newRoot->left;
                newRoot->left->parent = oldRoot;
            }
            else {
                oldRoot->right = NULL;

            }
            newRoot->left = oldRoot;
            newRoot->parent = oldRoot->parent;
            if (newRoot->parent) {
                newRoot->parent->left = oldRoot->parent;
            }
            oldRoot->parent = newRoot;
            adjustHeight(oldRoot);
            adjustHeight(newRoot);
            return newRoot;

        }

        Node *balanceTree(Node *inserted) {
            bool flag = false;
            Node *tmpInserted = inserted;
            do {
                //std::cout << ratioNode(inserted) << " = " << inserted->height << " - " << inserted->left->height << " - (" << inserted->height << " - (-1) )" << std::endl;
                inserted = inserted->parent;
                if (inserted == _root)
                    flag = true;
                if (ratioNode(inserted) < -1) {
                    if (inserted->left->right && inserted->left->right->height > 0) {
                        inserted->left = rotateLeft(inserted->left);
                        inserted = rotateRight(inserted);
                    }
                    else {
                        inserted = rotateRight(inserted);
                    }
                    if (flag) {
                        break;
                    }
                }
                else if (ratioNode(inserted) > 1) {
                    if (inserted->left->right && inserted->left->right->height > 0) {
                        inserted->right = rotateRight(inserted->right);
                        inserted = rotateLeft(inserted);
                    }
                    else {
                        inserted = rotateLeft(inserted);
                    }
                    if (flag)
                        break;
                }
            } while (inserted != _root);
            
            return (inserted); // return le nouveau _root
        }
};

int main() {
    myMap<int> tree;
    tree.insert(5);
    std::cout << "root : height: " << tree._root->height << "_size : " << tree._size << " value : " << tree._root->data << std::endl;
    std::cout << std::endl;
    tree.insert(6);
    myMap<int>::Node *inserted = tree.insert(2);
    inserted = tree.insert(1);
    inserted = tree.insert(4);
    inserted = tree.insert(3);
    tree._root = tree.balanceTree(inserted);
    std::cout << "root : height: " << tree._root->height << "_size : " << tree._size << " value : " << tree._root->data << std::endl;
//    std::cout << "->left: height: " << tree._root->left->height << "_size : " << tree._size << " value : " << tree._root->left->data << std::endl;
//    std::cout << "->right: height: " << tree._root->right->height << "_size : " << tree._size << " value : " << tree._root->right->data << std::endl;
//    std::cout << "->left->left: height: " << tree._root->left->left->height << "_size : " << tree._size << " value : " << tree._root->left->left->data << std::endl;
//    std::cout << "->left->right: height: " << tree._root->left->right->height << "_size : " << tree._size << " value : " << tree._root->left->right->data << std::endl;
    //std::cout << "->left->right->left: height: " << tree._root->left->right->left->height << "_size : " << tree._size << " value : " << tree._root->left->right->left->data << std::endl;



}