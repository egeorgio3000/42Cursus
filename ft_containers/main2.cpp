#ifndef STD

#include "vector.hpp"
#include "stack.hpp"
#else
#include <map>
#include <stack>
#include <utility>
#include <vector>
namespace ft = std;
#endif

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <unistd.h>

void print_test_time(const std::string test_name, const struct timeval &start)
{
    struct timeval end;
    std::string tabbed = "    ";
    tabbed += test_name;
    gettimeofday(&end, NULL);
    std::cout
        << tabbed << " tests time: " << (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec) << "us" << std::endl;
}
void stack_tests() {

    /////////////////////////////////////////////////////////////////////////////////
    //                    START OF STACK TESTS                                     //
    /////////////////////////////////////////////////////////////////////////////////
#ifndef STD
        std::cout << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                              FT::STACK TESTS                               //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << std::endl;
#else
        std::cout << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                              STD::STACK TESTS                              //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << std::endl;
#endif


    struct timeval start;
    gettimeofday(&start, NULL);
    ft::stack<int> stackA;

    std::cout << "    // <stack> member function push():" << std::endl
                  << std::endl;
    for (int i(0); i != 10; ++i) {
            std::cout << "    stackA.push(" << i << ");" << std::endl;

        stackA.push(i);
    }

        std::cout << std::endl
                  <<  "    // <stack> operator=:" << std::endl
                  << std::endl
                  << "    ft::stack<int>stackB = stackA" << std::endl;

    ft::stack<int> stackB = stackA;

    std::cout << std::endl
                  << "    // <stack> member functions top() / pop() / size():"  << std::endl
                  << std::endl;

    while (stackA.size()) {
        std::cout << "    stackA.size() = " << stackA.size() << std::endl;
        std::cout << "    stackA.top() = " << stackA.top() << std::endl;
        std::cout << "    stackA.pop()" << std::endl;
        stackA.pop();
    }

    std::cout << std::endl
                  << "    // <stack> relational operators and member function empty():" << std::endl
                  << std::endl;
        std::cout << "    stackA == stackB: " << (stackA == stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA != stackB: " << (stackA != stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA < stackB: " << (stackA < stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA > stackB: " << (stackA > stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA <= stackB: " << (stackA <= stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA >= stackB: " << (stackA >= stackB ? "true" : "false") << std::endl;
        std::cout << "    stackA.empty(): " << (stackA.empty() ? "true" : "false") << std::endl;
        std::cout << std::endl;


#ifndef STD
    print_test_time("ft::stack", start);
#else
    print_test_time("std::stack", start);
#endif

    /////////////////////////////////////////////////////////////////////////////////
    //                    END OF STACK TESTS                                       //
    /////////////////////////////////////////////////////////////////////////////////
}
void vector_tests()
{
#ifndef STD
        std::cout << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                              FT::VECTOR TESTS                               //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << std::endl;
#else
        std::cout << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                              STD::VECTOR TESTS                              //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << std::endl;
#endif

    struct timeval start;
    gettimeofday(&start, NULL);

    std::cout << "    // <vector> constructors:" << std::endl
              << std::endl;
    ft::vector<int> vectorA(3, 42);
    ft::vector<int> vectorB(vectorA);
    ft::vector<int> vectorC(vectorB.begin(), vectorB.end());
    ft::vector<int> vectorD = vectorC;

    for (unsigned int i(0); i != vectorA.size(); ++i)
    {
        std::cout << "    vectorA[" << i << "] = " << vectorA[i] << std::endl;
        std::cout << "    vectorB[" << i << "] = " << vectorB[i] << std::endl;
        std::cout << "    vectorC[" << i << "] = " << vectorC[i] << std::endl;
        std::cout << "    vectorD[" << i << "] = " << vectorD[i] << std::endl
                  << std::endl;
    }

    std::cout << "    // <vector> member function push_back():" << std::endl
              << std::endl;

    for (int i(0); i != 10; ++i)
    {
        std::cout << "    vectorA.push_back(" << i + 8 << ")" << std::endl;
        vectorA.push_back(i + 8);
    }

    std::cout << std::endl
              << "    // <vector> member functions at():" << std::endl
              << std::endl;

    for (unsigned int i(0); i != vectorB.size(); ++i)
        std::cout << "    vectorB.at(" << i << "): " << vectorB.at(i) << std::endl;
    std::cout << std::endl;
    for (unsigned int i(0); i != vectorA.size(); ++i)
        std::cout << "    vectorA.at(" << i << "): " << vectorA.at(i) << std::endl;
    std::cout << std::endl;


    std::cout << std::endl
              << "    // <vector> member functions insert():" << std::endl
              << std::endl;

    vectorB.insert(vectorB.begin(), 777);
    vectorB.insert(vectorB.begin() + 1, 3, 1337);
    vectorB.insert(vectorB.begin() + 1, vectorA.begin(), vectorA.end());
    vectorB.insert(vectorB.begin() + 2, 22);
    vectorB.insert(vectorB.begin() + 3, 333);
    vectorB.insert(vectorB.begin() + 4, 4444);
    vectorB.insert(vectorB.begin() + 5, 55555);

    for (unsigned int i(0); i != vectorB.size(); ++i)
        std::cout << "    vectorB.at(" << i << "): " << vectorB.at(i) << std::endl;

    std::cout << std::endl
              << "   // Trying to access an out of range value with at():" << std::endl;

    try
    {
        vectorB.at(vectorB.size());
    }
    catch (std::exception &e)
    {
        std::cout << "    " << e.what() << std::endl;
    }

    std::cout << std::endl
              << "    // <vector> member functions size() / capacity() / max_size():" << std::endl
              << std::endl
              << "    vectorA.size(): " << vectorA.size() << std::endl;
    std::cout << "    vectorA.capacity(): " << vectorA.capacity() << std::endl;
    std::cout << "    vectorA.max_size(): " << vectorA.max_size() << std::endl;
    std::cout << "    vectorB.size(): " << vectorB.size() << std::endl;
    std::cout << "    vectorB.capacity(): " << vectorB.capacity() << std::endl;
    std::cout << "    vectorB.max_size(): " << vectorB.max_size() << std::endl;

    std::cout << std::endl
              << "    // <vector> iterators:" << std::endl
              << std::endl;

    std::cout << "    Print vectorA from begin() to end():" << std::endl;
    for (ft::vector<int>::const_iterator it(vectorA.begin()); it != vectorA.end(); ++it)
        std::cout << "    vectorA[" << (it - vectorA.begin()) << "]: " << *it << std::endl;

    std::cout << std::endl;
    std::cout << "    Print vectorA from rbegin() to rend():" << std::endl;
    for (ft::vector<int>::const_reverse_iterator it(vectorA.rbegin()); it != vectorA.rend(); ++it)
        std::cout << "    vectorA[" << (it - vectorA.rbegin() + 1) << "]: " << *it << std::endl;

    std::cout << std::endl;
    std::cout << "    Test const_iterator and iterator compatibility:" << std::endl;
    ft::vector<int>::const_iterator const_iterator_begin(vectorB.begin());
    ft::vector<int>::iterator iterator_end(vectorB.end());
    for (; const_iterator_begin != iterator_end; ++const_iterator_begin)
        std::cout << "    vectorB[" << (const_iterator_begin - vectorB.begin()) << "]: " << *const_iterator_begin << std::endl;

    std::cout << std::endl;

    std::cout << std::endl
              << "    // <vector> member function swap():" << std::endl
              << std::endl;

    vectorB.swap(vectorA);

    std::cout << "    vectorA.size(): " << vectorA.size() << std::endl;
    std::cout << "    vectorA.capacity(): " << vectorA.capacity() << std::endl;
    std::cout << "    vectorA.max_size(): " << vectorA.max_size() << std::endl;
    std::cout << "    vectorB.size(): " << vectorB.size() << std::endl;
    std::cout << "    vectorB.capacity(): " << vectorB.capacity() << std::endl;
    std::cout << "    vectorB.max_size(): " << vectorB.max_size() << std::endl
              << std::endl;

    for (unsigned int i(0); i != vectorA.size(); ++i)
        std::cout << "    vectorA[" << i << "]: " << vectorA[i] << std::endl;

    std::cout << std::endl;

    for (unsigned int i(0); i != vectorB.size(); ++i)
        std::cout << "    vectorB[" << i << "]: " << vectorB[i] << std::endl;

    std::cout << std::endl;

    std::cout << std::endl
              << "    // <vector> member function erase():" << std::endl
              << std::endl;

    vectorB.erase(vectorB.begin() + 1, vectorB.end() - vectorB.size() / 2);

    for (unsigned int i(0); i != vectorB.size(); ++i)
        std::cout << "    vectorB.[" << i << "]: " << vectorB[i] << std::endl;
    std::cout << std::endl;

    std::cout << "    // <vector> resize():" << std::endl
              << std::endl;

    vectorA.resize(5, 42);
    vectorA.resize(10, 33);
    vectorA.resize(0, 1000);
    vectorA.resize(1, 42);

    for (unsigned int i(0); i != vectorA.size(); ++i)
        std::cout << "    vectorA.[" << i << "]: " << vectorA[i] << std::endl;
    std::cout << std::endl;

    std::cout << "    // <vector> reserve exception with reserve(max_size + 1):" << std::endl
              << std::endl;

    try
    {
        vectorA.reserve(vectorA.max_size() + 1);
    }
    catch (std::exception &e)
    {
            std::cout << "    " << e.what() << std::endl
                      << std::endl;
    }

#ifndef STD
    print_test_time("ft::vector", start);
#else
    print_test_time("std::vector", start);
#endif
}

int main() {
   // stack_tests();
    vector_tests();
}