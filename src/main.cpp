#include <iostream>
#include <cassert>
#include "TMatrix.h"

int main()
{
    std::cout << "Hello life!" << std::endl;

    int a=0;
    TMatrix<int, 5, 3> field;
    for (int i = 0; i < 3; i++)
        for(int j = 0; j < 5; j++)
            {
                field.at(i,j).value() = (++a)*2;
                //std::cout << field.at(i,j).value << "\t";
            }
    std::cout << std::endl;
    for (int i=-1; i>=-3; i--)
    {
        for (int j=-1; j>=-5; j--)
           std::cout << field.get(i,j).value() << "\t";
        std::cout << std::endl;
    }
    std::cout << std::endl << "Tests:" << std::endl;

    assert(field.at(1,3).value() == 18);
    std::cout << "OK" << std::endl;

    assert(field.get(-1,-3).value() == 26);
    std::cout << "OK" << std::endl;

    assert(field.get(10,28).value() == 18);
    std::cout << "OK" << std::endl;

    assert(field.at(-4,-13).value() == 26);
    std::cout << "OK" << std::endl;

    field.at(1,3).value() = 17;
    assert(field.get(1,3).value() == 17);
    std::cout << "OK" << std::endl;

    //field.get(1,3).value = 18;
    std::cout << "OK" << std::endl;


    for (auto a : field)
    {
        std::cout << a.value() << " ";
    }
    std::cout << "Foreach - OK" << std::endl;

    auto it = field.begin();
    assert(it->value() == 2);
    std::cout << "OK" << std::endl;

    ++it;
    assert(it->value() == 4);
    std::cout << "OK" << std::endl;

    ++it;
    it->value() = 5;
    assert(it->value() == 5);
    std::cout << "OK" << std::endl;

    assert(field.at(0,2).value() == 5);
    std::cout << "OK" << std::endl;

    const auto c_it = field.cbegin();
    assert(c_it->value() == 2);
    std::cout << "OK" << std::endl;

    c_it->value() = 1;
    assert(c_it->value() == 1);
    std::cout << "OK" << std::endl;

    assert(field.at(0,0).value() == 1);
    std::cout << "OK" << std::endl;

    assert(field.get(2,3).getCoordinates().first == 2);
    assert(field.get(2,3).getCoordinates().second == 3);
    std::cout << "OK" << std::endl;

    auto nbh_it = it->begin();
    assert(nbh_it->value() == 24);
    std::cout << "OK" << std::endl;

    assert((++(field.get(1,2).begin()))->value() == 5);
    std::cout << "OK" << std::endl;

    assert(field.begin()->begin()->value() == 30);
    std::cout << "OK" << std::endl;

    auto c = field.get(1,2);
    for (auto a : c)
         std::cout << a.value() << " ";
    std::cout << "Foreach - OK" << std::endl;

    for (auto a : field)
    {
        std::cout << a.value() << ": ";
        for (auto c : a)
            std::cout << c.value() << " ";
        std::cout << std::endl;
    }
    std::cout << "\nForeach - OK" << std::endl;
    return 0;
}
