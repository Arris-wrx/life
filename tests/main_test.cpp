#include <iostream>
#include <cassert>
#include "TMatrix.h"
#include "TPrint.h"
#include "TMatrixView.h"

int main()
{
    std::cout << "Hello life!" << std::endl;

    int a=0;
    TMatrix<int, 5, 3> field;
    for (int i = 0; i < 3; i++)
        for(int j = 0; j < 5; j++)
            {
                field.at(i,j) = (++a)*2;
                //std::cout << field.at(i,j).value << "\t";
            }

    field.print();

    std::cout << std::endl;
    for (int i=-1; i>=-3; i--)
    {
        for (int j=-1; j>=-5; j--)
           std::cout << field.get(i,j) << "\t";
        std::cout << std::endl;
    }
    std::cout << std::endl << "Tests:" << std::endl;

    assert(field.count() == 15);
    std::cout << "OK" << std::endl;

    assert(field.size().first == 3);
    assert(field.size().second == 5);
    std::cout << "OK" << std::endl;

    assert(field.at(1,3).value() == 18);
    std::cout << "OK" << std::endl;

    assert(field.get(-1,-3).value() == 26);
    std::cout << "OK" << std::endl;

    assert(field.get(10,28).value() == 18);
    std::cout << "OK" << std::endl;

    assert(field.at(-4,-13).value() == 26);
    std::cout << "OK" << std::endl;

    field.at(1,3) = 17;
    assert(field.get(1,3).value() == 17);
    std::cout << "OK" << std::endl;

    field.get(1,3) = 18; // does not modificate
    assert(field.get(1,3).value() == 17);
    std::cout << "OK" << std::endl;


    for (auto a : field)
    {
        std::cout << a << " ";
    }
    std::cout << "Foreach - OK" << std::endl;

    for (auto &it : field)
    {
        std::cout << it << " ";
    }
    std::cout << "Ref Foreach - OK" << std::endl;

    print(field);
    std::cout << "OK" << std::endl;

    printRef(field);
    std::cout << "OK" << std::endl;

    auto it = field.begin();
    assert(it->value() == 2);
    std::cout << "OK" << std::endl;

    ++it;
    assert(it->value() == 4);
    std::cout << "OK" << std::endl;

    ++it;
    *(it) = 5;
    assert(it->value() == 5);
    std::cout << "OK" << std::endl;

    assert(field.at(0,2).value() == 5);
    std::cout << "OK" << std::endl;

    const TMatrix<int, 5, 3> mat(field);
    const auto c_it = mat.cbegin();
    assert(c_it->value() == 2);
    std::cout << "OK" << std::endl;

    //*(c_it) = 1;
    std::cout << "OK" << std::endl;

    assert(field.at(0,0).value() == 2);
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
            std::cout << c << " ";
        std::cout << std::endl;
    }
    std::cout << "Cell Iterator - OK" << std::endl;

    mat.print();
    std::cout << "Print - OK" << std::endl;

    TMatrix<int, 5, 3> mat1;
    mat1 = field.calculate([](auto it){
        int t {0};
        for (auto c : it)
            t += c.value();
        return t;
    });

    assert(mat1.get(1,2).value() == 126);
    mat1.print();
    std::cout << "Calc - OK" << std::endl;

    MatrixView <int, 5, 3> view(field, 1, 4, 0, 2);
    view.print();
    std::cout << "View - OK" << std::endl;

    view.at(1,1) = 10;
    view.print();
    field.print();

    return 0;
}
