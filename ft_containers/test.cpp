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
    ft::vector<int> fv1(5, 1), fv2(1, 1), fv3(2, 1), fv4(2, 2);
    std::vector<int> sv1, sv2(1, 1), sv3(1, 1), sv4(2, 2);
    ft::vector<int>::iterator it = fv1.begin();
    fv1.insert(fv1.begin() + 1, 4);
    fv2.insert(fv2.begin(), 2 , 2);
    fv3.insert(fv3.begin(), fv4.begin(), fv4.end());
    //print_vector(fv1);
    //print_vector(fv2);
    print_vector(fv3);
    sv1.insert(sv1.begin(), 4);
    sv2.insert(sv2.begin(), 2, 2);
    sv3.insert(sv3.begin(), sv4.begin(), sv4.end());
    //print_vector(sv2);
    print_vector(sv3);

    return 0;
}