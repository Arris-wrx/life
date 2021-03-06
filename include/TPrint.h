#ifndef TPRINT_H
#define TPRINT_H

#include <iostream>

// template array print func
template < class T >
void print(T m) {
    for (auto &it : m) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

// template array print ref func
template < class T >
void printRef(const T& m) {
    for (auto &it : m) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}


#endif // TPRINT_H
