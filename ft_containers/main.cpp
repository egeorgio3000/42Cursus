#include <vector>
#include "vector.hpp"

#include <iostream>
#include <memory>
#include <sys/time.h>
#define DEBUG 1

template<typename T>
void    compare_vector(std::vector<T> const &stdvec, ft::vector<T> const &ftvec) {
    int flag = 0, flag2 = 0;
    if (stdvec.capacity() != ftvec.capacity() || DEBUG) {
        std::cout << "error capacity: FT: " << ftvec.capacity() << ", STD: " << stdvec.capacity() << std::endl;
        flag = 1;
    }
    if (stdvec.size() != ftvec.size() || DEBUG) {
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
    if (flag2 || DEBUG) {
        if (flag2)
            std::cout << "error vector data :\n";
        std::cout << "FT: ";
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

            stdvec4.insert(stdvec4.end(), 1, 3);
            ftvec4.insert(ftvec4.end(), 1, 3);
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

            std::cout << "push_back: ";
            stdvec.push_back(3);
            ftvec.push_back(3);
            compare_vector<int>(stdvec, ftvec);

            std::cout << "insert: ";
            std::vector<int>::iterator stdit1 = stdvec.begin(), stdit2 = stdit1 + 3;
            ft::vector<int>::iterator ftit1 = ftvec.begin(), ftit2 = ftit1 + 3;
            stdit1 = stdvec.insert(stdit2, 4);
            ftit1 = ftvec.insert(ftit2, 4);
            if (DEBUG)
                std::cout << std::endl << "STD return: " << stdit1 - stdvec.begin() << ", FT return: " << ftit1 - ftvec.begin() << std::endl;
            compare_vector<int>(stdvec, ftvec);

            std::cout << "n datas: ";
            stdit1 = stdvec.begin(), stdit2 = stdit1 + 1;
            ftit1 = ftvec.begin(), ftit2 = ftit1 + 1;
            stdvec.insert(stdit2, 3, 4);
            ftvec.insert(ftit2, 3, 4);
            compare_vector<int>(stdvec, ftvec);

            std::cout << "vois insert from InputIterator: ";
            ft::vector<int> ftvec3(3, 8);
            std::vector<int> stdvec3(3, 8);
            stdvec.insert<std::vector<int>::iterator>(stdvec.begin() + 1, stdvec3.begin() , stdvec3.end());
            ftvec.insert<ft::vector<int>::iterator>(ftvec.begin() + 1, ftvec3.begin(), ftvec3.end());
            compare_vector<int>(stdvec, ftvec);

            std::cout << "reserve -: ";
            stdvec.reserve(2);
            ftvec.reserve(2);
            compare_vector<int>(stdvec, ftvec);

            std::cout << "reserve +: ";
            stdvec.reserve(8);
            ftvec.reserve(8);
            compare_vector<int>(stdvec, ftvec);

            std::cout << "erase 1: ";
            ftit1 = ftvec.begin() + 4;
            stdit1 = stdvec.begin() + 4;
            stdit1 = stdvec.erase(stdit1);
            ftit1 = ftvec.erase(ftit1);
            if (DEBUG)
                std::cout << std::endl << "STD return: " << stdit1 - stdvec.begin() << ", FT return: " << ftit1 - ftvec.begin() << std::endl;
            compare_vector<int>(stdvec, ftvec);

            std::cout << "erase severals: ";
            stdit1 = stdvec.erase(stdvec.begin(), stdvec.begin() + 1);
            ftit1 = ftvec.erase(ftvec.begin(), ftvec.begin() + 1);
            if (DEBUG)
                std::cout << std::endl << "STD return: " << stdit1 - stdvec.begin() << ", FT return: " << ftit1 - ftvec.begin() << std::endl;
            compare_vector<int>(stdvec, ftvec);

            std::cout << "pop_back: ";
            stdvec.pop_back();
            ftvec.pop_back();
            compare_vector<int>(stdvec, ftvec);

            std::cout << "resize shorter: ";
            stdvec.resize(5);
            ftvec.resize(5);
            compare_vector<int>(stdvec, ftvec);

            std::cout << "resize larger: ";
            stdvec.resize(8);
            ftvec.resize(8);
            compare_vector<int>(stdvec, ftvec);
            
            std::cout << "resize shorter with init: ";
            stdvec.resize(4, 6);
            ftvec.resize(4, 6);
            compare_vector<int>(stdvec, ftvec);

            std::cout << "resize larger: ";
            stdvec.resize(7, 10);
            ftvec.resize(7, 10);
            compare_vector<int>(stdvec, ftvec);

            std::cout << "swap: " << std::endl << "vec: ";
            ft::vector<int> ftvec2(3, 8);
            std::vector<int> stdvec2(3, 8);
            stdvec.swap(stdvec2);
            ftvec.swap(ftvec2);
            compare_vector<int>(stdvec, ftvec);
            std::cout << "vec2: ";
            compare_vector<int>(stdvec2, ftvec2);

            ftvec.clear();
            stdvec.clear();
            ftvec.push_back(1);
            ftvec.push_back(2);
            ftvec.push_back(3);
            ftvec.push_back(4);
            ftvec.push_back(5);            
            stdvec.push_back(1);
            stdvec.push_back(2);
            stdvec.push_back(3);
            stdvec.push_back(4);
            stdvec.push_back(5);
            std::cout << "arithmetic iterators" << std::endl;
            ft::vector<int>::const_reverse_iterator fit1 = ftvec.rbegin(), fit2 = ftvec.rend();
            std::vector<int>::const_reverse_iterator sit1 = stdvec.rbegin(), sit2 = stdvec.rend();
            std::cout << fit1 - fit2 << std::endl;
            std::cout << sit1 - sit2 << std::endl;
            std::cout << "ft: " << *(fit1++) << " " << *(++fit1) << " " << *(fit1--) << " " << *(--fit1) << " " << *(fit2 - 1) << " " << *(fit1 + 1) << " " << fit1 - fit2 << std::endl;
            std::cout << "std: " << *(sit1++) << " " << *(++sit1) << " " << *(sit1--) << " " << *(--sit1) << " " << *(sit2 - 1) << " " << *(sit1 + 1) << " " << sit1 - sit2 << std::endl;
            
            
            std::cout << std::endl;
            std::cout << " iterator comparison: " << std::endl;
            std::cout << (sit1 == sit2) << std::endl;
            std::cout << (fit1 == fit2) << std::endl;            
            std::cout << (sit1 != sit2) << std::endl;
            std::cout << (fit1 != fit2) << std::endl;
            std::cout << (sit1 <= sit2) << std::endl;
            std::cout << (fit1 <= fit2) << std::endl;
            std::cout << (sit1 > sit2) << std::endl;
            std::cout << (fit1 > fit2) << std::endl;
            }
    }
}