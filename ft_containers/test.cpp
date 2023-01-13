#include <iostream>
#include <memory>
#include <vector>
#include "vector.hpp"
int main() {
    //std::allocator<int> alloc;
    ft::vector<int>::size_type n = 9;
    ft::vector<int> myvec(9, 2);
    std::vector<int> stdvec(9, 2);
    std::cout << myvec.size() << " " << stdvec.size() << std::endl;
    std::cout << myvec.capacity() << " " << stdvec.capacity() << std::endl;

    ft::vector<int>::iterator it1 = myvec.begin();
    std::vector<int>::iterator it2 = stdvec.begin();

    stdvec.erase(7);
    return 0;
}