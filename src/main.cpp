#include <iostream>
#include "TField.h"
#include "Cell.h"

int main()
{
    std::cout << "Hello life!" << std::endl;

    TField<int, 5, 3> field;
    for (int i = 0; i < 15; i++)
    {
        field[i] = i*2;
    }

    for (int i=-1; i>=-3; i--)
    {
        for (int j=-1; j>=-5; j--)
           std::cout << field(i,j) << "\t";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (auto a : field)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;


    return 0;
}
