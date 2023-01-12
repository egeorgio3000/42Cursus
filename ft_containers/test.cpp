#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::allocator<int> alloc;
    int *p = alloc.allocate(5);
 /*   alloc.construct(p, 1);
    alloc.construct(p + 1, 2);
    alloc.construct(p + 2, 3);
    alloc.construct(p + 3, 4);
    alloc.construct(p + 4, 5);
    alloc.deallocate(p, 5);
    p = alloc.allocate(8);
    for (int i =0; i < 5; i++)
        std::cout << *(p + i) << std::endl;*/
    std::vector<int> vec(3,42);
    std::vector<int>::iterator it;
    //vec.assign(15, 4);
   // vec.assign(3,8);
    vec.reserve(4);
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
    
    std::cout << vec.capacity() << " " << vec.size() << std::endl;
    it = vec.insert(vec.end(), 5,  7);

    //std::cout << *it << " " << *(vec.end() - 1) << std::endl;
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
    std::cout << vec.capacity() << " " << vec.size() << std::endl;

}