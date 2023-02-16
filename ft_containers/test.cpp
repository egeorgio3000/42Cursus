#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"


template <typename Key, typename T>
void print_map(ft::map<Key, T> const &map) {
    std::cout << "MY MAP: " << std::endl;
    typename ft::map<Key, T>::const_iterator it = map.begin();
    for (; it != map.end(); it++) {
        std::cout << "key= " << it->first << ", value= " << it->second << " ";
    }
    std::cout << std::endl << "Size: " << map.size() << std::endl;
}

template <typename Key, typename T>
void print_map(std::map<Key, T> const &map) {
    std::cout << "STD MAP: " << std::endl;
    typename std::map<Key, T>::const_iterator it = map.begin();
    for (; it != map.end(); it++) {
        std::cout << "key= " << it->first << ", value= " << it->second << " ";
    }
    std::cout << std::endl << "Size: " << map.size() << std::endl;
}

int main() {

    ft::map<int, std::string> ftmap;
    print_map(ftmap);
    ftmap.insert(ft::pair<int, std::string>(5, "cinq"));
    print_map(ftmap);
    ftmap.insert(ft::pair<int, std::string>(1, "un"));
    print_map(ftmap);
    return 0;
}