#include <iostream>
#include <memory>
#include <vector>
#include "vector.hpp"
template <typename T>
void print_vector(ft::vector<T> vec) {
    std::cout << "MY VEC: " << std::endl;
    for (typename ft::vector<T>::size_type i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl << "Size: " << vec.size() << std::endl << "Capacity: " << vec.capacity() << std::endl;
}
template <typename T>
void print_vector(std::vector<T> vec) {
    std::cout << "STD VEC: " << std::endl;
    for (typename ft::vector<T>::size_type i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl << "Size: " << vec.size() << std::endl << "Capacity: " << vec.capacity() << std::endl;
}

int main() {
    //std::allocator<int> alloc;
    ft::vector<int>::size_type n = 9;
    ft::vector<int> myvec(9, 2);
    std::vector<int> stdvec(9, 2);
    print_vector(myvec);
    print_vector(stdvec);
    ft::vector<int>::iterator it1 = myvec.end();
    std::vector<int>::iterator it2 = stdvec.end();
    myvec.push_back(3);
    stdvec.push_back(3);
    print_vector(myvec);
    print_vector(stdvec);
    std::cout << *(it1) << " " << *(it2) << std::endl;
    return 0;
}