#ifndef STD

#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "pair.hpp"
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

    std::cout << std::endl
                  << "    // <vector> relational operators and member function empty():" << std::endl
                  << std::endl;
    std::cout << "    vectorA == vectorB: " << (vectorA == vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA != vectorB: " << (vectorA != vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA < vectorB: " << (vectorA < vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA > vectorB: " << (vectorA > vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA <= vectorB: " << (vectorA <= vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA >= vectorB: " << (vectorA >= vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA.empty(): " << (vectorA.empty() ? "true" : "false") << std::endl;
    std::cout << std::endl;
    
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

    std::cout << std::endl
                  << "    vectorA.clear() and vectorB.clear():" << std::endl
                  << std::endl;
    vectorA.clear();
//    vectorB.clear();
    std::cout << std::endl
                  << "    // <vector> relational operators and member function empty():" << std::endl
                  << std::endl;
    std::cout << "    vectorA == vectorB: " << (vectorA == vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA != vectorB: " << (vectorA != vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA < vectorB: " << (vectorA < vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA > vectorB: " << (vectorA > vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA <= vectorB: " << (vectorA <= vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA >= vectorB: " << (vectorA >= vectorB ? "true" : "false") << std::endl;
    std::cout << "    vectorA.empty(): " << (vectorA.empty() ? "true" : "false") << std::endl;
    std::cout << std::endl;
#ifndef STD
    print_test_time("ft::vector", start);
#else
    print_test_time("std::vector", start);
#endif
}

void pair_tests() {

    /////////////////////////////////////////////////////////////////////////////////
    //                    START OF PAIR TESTS                                      //
    /////////////////////////////////////////////////////////////////////////////////

#ifndef STD
        std::cout << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                               FT::PAIR TESTS                                //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << std::endl;
#else
        std::cout << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                               STD::PAIR TESTS                               //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << std::endl;
#endif

    struct timeval start;
    gettimeofday(&start, NULL);
    ft::pair<unsigned int, unsigned int> pairA(1, 2);


    std::cout << "    // <pair> constructors and make_pair():" << std::endl << std::endl;

    ft::pair<unsigned int, unsigned int> pairB = ft::make_pair(3, 4);
    ft::pair<unsigned int, unsigned int> pairC = pairB;
    ft::pair<unsigned int, unsigned int> pairD(pairC);


    std::cout << "    pairA.first: " << pairA.first << std::endl;
    std::cout << "    pairA.second: " << pairA.second << std::endl;
    std::cout << "    pairB.first: " << pairB.first << std::endl;
    std::cout << "    pairB.second: " << pairB.second << std::endl;
    std::cout << "    pairA.first = 3: " << (pairA.first = 3) << std::endl;
    std::cout << "    pairA.second = 4: " << (pairA.second = 4) << std::endl;
    std::cout << "    pairB.first = 5: " << (pairB.first = 5) << std::endl;
    std::cout << "    pairB.second = 6: " << (pairB.second = 6) << std::endl;
    std::cout << std::endl;


    std::cout << "    // <pair> relational operators:" << std::endl
                << std::endl;
    std::cout << "    pairA == pairB: " << (pairA == pairD ? "true" : "false") << std::endl;
    std::cout << "    pairA != pairB: " << (pairA != pairB ? "true" : "false") << std::endl;
    std::cout << "    pairA < pairB: " << (pairA < pairC ? "true" : "false") << std::endl;
    std::cout << "    pairA <= pairB: " << (pairA <= pairB ? "true" : "false") << std::endl;
    std::cout << "    pairA > pairB: " << (pairA > pairC ? "true" : "false") << std::endl;
    std::cout << "    pairA >= pairB: " << (pairA >= pairD ? "true" : "false") << std::endl;
    std::cout << std::endl;


#ifndef STD
    print_test_time("ft::pair", start);
#else
    print_test_time("std::pair", start);
#endif
}

void map_tests() {

    ///////////////////////////////////////////////////////////////////////////////////
    ////                     START OF MAP TESTS                                      //
    ///////////////////////////////////////////////////////////////////////////////////



#ifndef STD
        std::cout << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                            FT::MAP TESTS                                    //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << std::endl;
#else
        std::cout << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << "    //                            STD::MAP TESTS                                   //" << std::endl
                  << "    /////////////////////////////////////////////////////////////////////////////////" << std::endl
                  << std::endl;
#endif


    struct timeval start;
    gettimeofday(&start, NULL);


    std::cout << std::endl
    << "    // <map> default constructor, insert(pair) and insert(hint, key):" << std::endl
    << std::endl;

    ft::map<int, int> mapA;
    for (int i(0); i != 9; ++i) {
        std::cout << "    mapA.insert(" << i << ", " << i << ")" << std::endl;
        mapA.insert(ft::make_pair(i, i));
    }


    std::cout << "    mapA.insert(mapA.begin(), ft::make_pair(9, 9)); x3" << std::endl;
    mapA.insert(mapA.begin(), ft::make_pair(9, 9));
    mapA.insert(mapA.begin(), ft::make_pair(9, 9));
    mapA.insert(mapA.begin(), ft::make_pair(9, 9));


    std::cout << std::endl
                  << "    // <map> copy constructors and iterators:" << std::endl
                  << std::endl;
    
    ft::map<int, int> mapB(mapA);
    ft::map<int, int> mapC(mapB.begin(), mapB.end());
    std::cout << "test2" << std::endl;
    ft::map<int, int> mapD;
    std::cout << "test3" << std::endl;
    mapD = mapC;
    std::cout << "test4" << std::endl;
    // print content of all maps and check iterators compatiblity
    ft::map<int, int>::const_iterator const_iterator_begin = mapA.begin();
    ft::map<int, int>::iterator iterator_end = mapA.end();
    for (; const_iterator_begin != iterator_end; ++const_iterator_begin) {
        std::cout << "    mapA[" << const_iterator_begin->first << "]: " << const_iterator_begin->second << std::endl;
    }
    std::cout << std::endl;
    for (ft::map<int, int>::const_iterator it(mapB.begin()); it != mapB.end(); ++it) {
        std::cout << "    mapB[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl;
    for (ft::map<int, int>::const_iterator it(mapC.begin()); it != mapC.end(); ++it) {
        std::cout << "    mapC[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl;
    for (ft::map<int, int>::const_iterator it(mapD.begin()); it != mapD.end(); ++it) {
        std::cout << "    mapD[" << it->first << "]: " << it->second << std::endl;
    }


    std::cout << std::endl
                << "    Print MapB in reverse order with iterator--" << std::endl
                << std::endl;
    for (ft::map<int, int>::iterator it(mapB.end()); it != mapB.begin();) {
        --it;
        std::cout << "    mapB[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl;



    std::cout << "    // <map> size() and empty():" << std::endl
                << std::endl;
    std::cout << "    mapA.size(): " << mapA.size() << std::endl;
    std::cout << "    is mapA empty: " << mapA.empty() << std::endl;
    std::cout << "    mapB.size(): " << mapB.size() << std::endl;
    std::cout << "    is mapB empty: " << mapB.empty() << std::endl;
    std::cout << "    mapC.size(): " << mapC.size() << std::endl;
    std::cout << "    is mapC empty: " << mapC.empty() << std::endl;
    std::cout << "    mapD.size(): " << mapD.size() << std::endl;
    std::cout << "    is mapD empty: " << mapD.empty() << std::endl
                << std::endl;

    std::cout << "    // <map> erase(key), erase(iterator) and erase(first, last):" << std::endl
                << std::endl;

    std::cout << "    mapA.erase(3)" << std::endl;
    std::cout << "    mapA.erase(begin())" << std::endl
                << std::endl;

    mapA.erase(3);
    mapA.erase(mapA.begin());

    std::cout << std::endl
                << "    mapA.size(): " << mapA.size() << std::endl
                << "    is mapA empty: " << mapA.empty() << std::endl;
    for (ft::map<int, int>::const_iterator it(mapA.begin()); it != mapA.end(); ++it) {
        std::cout << "    mapA[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl;

    std::cout << "    mapA.erase(begin(), end())" << std::endl;
    mapA.erase(mapA.begin(), mapA.end());

    std::cout << std::endl
                << "    mapA.size(): " << mapA.size() << std::endl
                << "    is mapA empty: " << mapA.empty() << std::endl;
    for (ft::map<int, int>::const_iterator it(mapA.begin()); it != mapA.end(); ++it) {
        std::cout << "    mapA[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl;



    std::cout << "    // <map> insert(first, last):" << std::endl
                << std::endl
                << "    mapA.insert(mapB.begin(), mapB.end())" << std::endl
                << std::endl;

    mapA.insert(mapB.begin(), mapB.end());


    std::cout << std::endl
                << "    mapA.size(): " << mapA.size() << std::endl
                << "    is mapA empty: " << mapA.empty() << std::endl;
    for (ft::map<int, int>::const_iterator it(mapA.begin()); it != mapA.end(); ++it) {
        std::cout << "    mapA[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl;



    std::cout << "    // <map> clear() and swap():" << std::endl
                << std::endl
                << "    Clear mapB and fill it with random number:" << std::endl;

    mapB.clear();
    for (int i(0); i != 10000; ++i) {
        mapB.insert(ft::make_pair(i, rand() % 10000));
    }


    std::cout << std::endl
                << "    mapA.size(): " << mapA.size() << std::endl
                << "    is mapA empty: " << mapA.empty() << std::endl;
    for (ft::map<int, int>::const_iterator it(mapA.begin()); it != mapA.end(); ++it) {
        std::cout << "    mapA[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl
                << "    mapB.size(): " << mapB.size() << std::endl
                << "    is mapB empty: " << mapB.empty() << std::endl;
    for (ft::map<int, int>::const_iterator it(mapB.begin()); it != mapB.end(); ++it) {
        std::cout << "    mapB[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl;



    std::cout << "    mapA.swap(mapB)" << std::endl;
    mapA.swap(mapB);


    std::cout << std::endl
                << "    mapA.size(): " << mapA.size() << std::endl
                << "    is mapA empty: " << mapA.empty() << std::endl;
    for (ft::map<int, int>::const_iterator it(mapA.begin()); it != mapA.end(); ++it) {
        std::cout << "    mapA[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl
                << "    mapB.size(): " << mapB.size() << std::endl
                << "    is mapB empty: " << mapB.empty() << std::endl;
    for (ft::map<int, int>::const_iterator it(mapB.begin()); it != mapB.end(); ++it) {
        std::cout << "    mapB[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl;


    std::cout << "    // filling mapE<char, unsigned int> with letters:" << std::endl;

    ft::map<char, unsigned int> mapE;
    for (int i(0); i != 26; ++i) {
        char letter = 'a' + i;
        mapE.insert(ft::make_pair(letter, i + 1));
    }


    std::cout << std::endl;
    for (ft::map<char, unsigned int>::const_iterator it(mapE.begin()); it != mapE.end(); ++it) {
        std::cout << "    mapE[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl;



    std::cout << "    // <map> find() and count():" << std::endl
                << std::endl
                << "    mapB.find(3): " << mapB.find(3)->second << std::endl
                << "    mapB.count(3): " << mapB.count(3) << std::endl
                << "    mapB.find(100): " << mapB.find(100)->second << std::endl
                << "    mapB.count(100): " << mapB.count(100) << std::endl
                << std::endl;


    std::cout << "    // <map> lower_bound() and upper_bound():" << std::endl
                << std::endl
                << "    mapB.lower_bound(3): " << mapB.lower_bound(3)->second << std::endl
                << "    mapB.upper_bound(3): " << mapB.upper_bound(3)->second << std::endl
                << "    mapB.lower_bound(100): " << mapB.lower_bound(100)->second << std::endl
                << "    mapB.upper_bound(100): " << mapB.upper_bound(100)->second << std::endl
                << std::endl;


    std::cout << "    // <map> equal_range():" << std::endl
                << std::endl
                << "    mapB.equal_range(3): " << mapB.equal_range(3).first->second << " "
                << mapB.equal_range(3).second->second << std::endl
                << "    mapB.equal_range(100): " << mapB.equal_range(100).first->second << " "
                << mapB.equal_range(100).second->second << std::endl
                << std::endl;


    std::cout << "    // <map> operator[]:" << std::endl
                << std::endl
                << "    mapB[3]: " << mapB[3] << std::endl
                << "    mapB[100]: " << mapB[100] << std::endl
                << std::endl;

    std::cout << "    // <map> relational operators:" << std::endl
                << std::endl
                << "    mapA == mapB: " << (mapA == mapB) << std::endl
                << "    mapA != mapB: " << (mapA != mapB) << std::endl
                << "    mapA < mapB: " << (mapA < mapB) << std::endl
                << "    mapA <= mapB: " << (mapA <= mapB) << std::endl
                << "    mapA > mapB: " << (mapA > mapB) << std::endl
                << "    mapA >= mapB: " << (mapA >= mapB) << std::endl
                << std::endl;


    std::cout << "    // <map> reverse iterators:" << std::endl
                << std::endl;
    for (ft::map<int, int>::reverse_iterator it(mapD.rbegin()); it != mapD.rend(); it++) {
        std::cout << "    mapD[" << it->first << "]: " << it->second << std::endl;
    }
    std::cout << std::endl;
    
#ifndef STD
    print_test_time("ft::map", start);
#else
    print_test_time("std::map", start);
#endif
}

int main(int ac, char **av) {
    if (ac == 1) {
        std::cout << "printing all tests:" << std::endl << std::endl;
        stack_tests();
        vector_tests();
        pair_tests();
        map_tests();
    }
    else {
        int flag = 0;
        ft::vector<char *> command;
        for (int i = 1; i < ac; i++) {
            
            if (std::string("stack").compare(av[i])
            && std::string("vector").compare(av[i])
            && std::string("pair").compare(av[i])
            && std::string("map").compare(av[i])) {
                flag = 1;
                break;
            }
            command.push_back(av[i]);
        }
        if (flag) {
            std::cout << "Wrong entry : plz enter \"";
#ifndef STD
            std::cout << "./ft_containers\" ";
#else
            std::cout << " ./std_containers\" ";
#endif
            std::cout << "for all tests and with the arguments \"stack\" \"vector\" \"pair\" \"map\" for specifics tests\n";
        }
        else {
            for (ft::vector<char *>::iterator it = command.begin(); it != command.end(); it++)
                if (std::string(*it) == std::string("stack"))
                    stack_tests();
                else if (std::string(*it) == std::string("vector"))
                    vector_tests();
                else if (std::string(*it) == std::string("pair"))
                    pair_tests();
                else if (std::string(*it) == std::string("map"))
                    map_tests();
        }
    }
    return 0;
}