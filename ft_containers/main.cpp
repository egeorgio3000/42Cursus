#include <iostream>
#include <memory>
#include <vector>
#include "vector.hpp"

template<typename T>
void    compare_vector(std::vector<T> const &stdvec, ft::vector<T> const &ftvec) {
    int flag = 0, flag2 = 0;
    if (stdvec.capacity() != ftvec.capacity()) {
        std::cout << "error capacity: FT: " << ftvec.capacity() << ", STD: " << stdvec.capacity() << std::endl;
        flag = 1;
    }
    if (stdvec.size() != ftvec.size()) {
        std::cout << "error size: FT: " << ftvec.size() << ", STD: " << stdvec.size() << std::endl;
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
        std::cout << "error vector data :\nFT: ";
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

template<typename T>
void    compare_functions(T const &stdf, T const &ftf) {
    if (stdf == ftf)
        std::cout << "OK !" << std::endl;
    else
        std::cout << "error : return of STD: " << stdf << ", FT: " << ftf << std::endl;
}



int main(int ac, char **av) {
    // vector tests 
    {
        std::cout << "/ / /   VECTOR TESTS   \\ \\ \\" << std::endl << std::endl;
        {
            std::cout << "CONSTRUCTORS" << std::endl << std::endl;
            std::cout << "default constructor: ";
            std::vector<int> stdvec1;
            ft::vector<int> ftvec1;
            compare_vector<int>(stdvec1, ftvec1);

            std::cout << "init constructor: ";
            std::vector<int> stdvec2(5, 1);
            ft::vector<int> ftvec2(5, 1);
            compare_vector<int>(stdvec2, ftvec2);

            std::cout << "copy constructor: ";
            std::vector<int> stdvec3(stdvec2);
            ft::vector<int> ftvec3(ftvec2);
            compare_vector<int>(stdvec3, ftvec3);

            std::cout << "iterator copy constructor: ";
            std::vector<int>::iterator stdit1 = stdvec2.begin(), stdit2 = stdit1 + 3;
            ft::vector<int>::iterator ftit1 = ftvec2.begin(), ftit2 = ftit1 + 3;
            std::vector<int> stdvec4(stdit1, stdit2);
            ft::vector<int> ftvec4(ftit1, ftit2);
            compare_vector(stdvec4, ftvec4);

            std::cout << "operator = : ";
            stdvec3 = stdvec4;
            ftvec3 = ftvec4;
            compare_vector<int>(stdvec3, ftvec3);
        }
        {
            std::cout << "MEMBER FUNCTIONS" << std::endl << std::endl;
            std::vector<int> stdvec(2, 1);
            ft::vector<int> ftvec(2, 1);

            std::cout << "push_back: ";
            stdvec.push_back(2);
            ftvec.push_back(2);
            compare_vector<int>(stdvec, ftvec);

            std::cout << "void insert :"
            stdvec.insert


        }
    }
}