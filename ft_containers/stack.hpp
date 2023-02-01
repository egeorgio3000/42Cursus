#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft {
template< typename T, class Container = ft::vector<T> >
class stack {
public:
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef Container container_type;

    explicit stack(const Container& container = Container()) : c(container) {}
    ~stack() {}

    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    value_type& top() { return c.back(); }
    const value_type& top() const { return c.back(); }
    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_back(); }

    template <class U, class C>
friend bool operator==(const stack<U, C> &x,
                const stack<U, C> &y);
template <class U, class C>
friend bool operator<(const stack<U, C> &x,
               const stack<U, C> &y);
template <class U, class C>
friend bool operator!=(const stack<U, C> &x,
                const stack<U, C> &y);
template <class U, class C>
friend bool operator>(const stack<U, C> &x,
               const stack<U, C> &y);
template <class U, class C>
friend bool operator>=(const stack<U, C> &x,
                const stack<U, C> &y);
template <class U, class C>
friend bool operator<=(const stack<U, C> &x,
                const stack<U, C> &y);
protected:
    container_type c;
};

template <class T, class Container>
bool operator==(const stack<T, Container> &x,
                const stack<T, Container> &y) { return x.c == y.c; }
template <class T, class Container>
bool operator<(const stack<T, Container> &x,
               const stack<T, Container> &y) { return x.c < y.c; }
template <class T, class Container>
bool operator!=(const stack<T, Container> &x,
                const stack<T, Container> &y) { return x.c != y.c; }
template <class T, class Container>
bool operator>(const stack<T, Container> &x,
               const stack<T, Container> &y) { return x.c > y.c; }
template <class T, class Container>
bool operator>=(const stack<T, Container> &x,
                const stack<T, Container> &y) { return x.c >= y.c; }
template <class T, class Container>
bool operator<=(const stack<T, Container> &x,
                const stack<T, Container> &y) { return x.c <= y.c; }
}
#endif