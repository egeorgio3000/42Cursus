#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::allocator<int> alloc;
    int *p = alloc.allocate(5);
    alloc.deallocate(p, 4); 
    std::vector<int> vec(9,2);
    std::vector<int>::iterator it;
    vec.assign(5, 4);
    for (size_t i = 0; i < vec.capacity(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    std::cout << vec.capacity() << " " << vec.size() << std::endl;

}