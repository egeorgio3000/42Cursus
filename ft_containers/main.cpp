#include <iostream>
#include <memory>
#include <vector>
#include "vector.hpp"

template<typename T>
void    compare_vector(std::vector<T> const &stdvec, ft::vector<T> const &ftvec) {
    int flag = 0, flag2 = 0;
    if (stdvec.capacity() != ftvec.capacity()) {
        std::cout << "error capacity: FT: " << ftvec.capacity() << ", STD: " << stdvec.capacity();
        flag = 1;
    }
    if (stdvec.size() != ftvec.size()) {
        std::cout << "error size: FT: " << ftvec.size() << ", STD: " << stdvec.size();
        flag2 = 1;
    }
    else {
        for (size_t i = 0; i < ftvec.size(); i++) {
            if (ftvec[i] != stdvec[i]) {
                flag2 = 1;
                break;
            }
        }
    }
    if (flag2) {
        std::cout << "error vector data :\nFT: "
        for (size_t i = 0; i < ftvec.size(); i++) {
            std::cout << ftvec[i] << " ";
        }
        std::cout << std::endl << "STD: ";
        for (size_t i = 0; i < stdvec.size(); i++) {
            std::cout << stdvec[i] << " ";
        }
        std::cout << std::endl;
    }
    if (!flag && !flag2)
        std::cout << "OK !" << std::endl;
}