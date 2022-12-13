#ifndef VECTOR_HPP
# define VECTOR _HPP

#include <iostream>
#include <memory>
#include <vector>
namespace ft {
    
template<typename T, class Allocator = std::allocator<T> >
class vector {
public:
    //  types:
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    //typedef implementation defined iterator; 
    //typedef implementation defined const_iterator; 
    typedef std::size_t size_type; 
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    //typedef ft::reverse_iterator<iterator> reverse_iterator;
    //typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    // construct/destroy:
    explicit vector(const allocator_type &allocator = Allocator()) : _alloc(allocator), _size(0), _capacity(0), _p(NULL) {    }
    explicit vector(size_type n, const value_type& value = value_type(), const allocator_type &allocator = Allocator()) : _alloc(allocator), _size(n), _capacity(n) {
        _p = _alloc.allocate(n);
        for (size_type i = 0; i < n; i++) {
            _alloc.construct(_p, value);
        }

    }
    
    template <typename InputIterator>
    vector(InputIterator first, InputIterator last, const allocator_type &allocator = Allocator()) {}
    vector(ft::vector<T, allocator_type> const& src) {}
    ~vector() {}

    //operators
    ft::vector<T, allocator_type> &operator=(ft::vector<T, allocator_type> const &rhs) {}

    //setters
    template <class InputIterator>
        void assign(InputIterator first, InputIterator last) {}
    void assign(size_type n, const T& u) {}

    //getters
    allocator_type  get_allocator() const { return _alloc; }

    //member functions
    iterator insert(iterator position, const T& x);
    void insert(iterator position, size_type n, const T& x);
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last);

private:
    allocator_type &_alloc;
    size_type       _size;
    size_type       _capacity;
    pointeur        _p;


};
}
#endif