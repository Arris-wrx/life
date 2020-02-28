#include <iostream>
#include <vector>
#include "TMatrix.h"
#include "TPrint.h"

int main()
{
    std::cout << "Hello life!" << std::endl;

    int a=0;
    TMatrix< int, 5, 3 > field;
    for (int i = 0; i < 3; i++)
        for(int j = 0; j < 5; j++)
            {
                field.at(i,j).value() = ( ++a )*2;
                //std::cout << field.at(i,j).value << "\t";
            }
    std::cout << std::endl;


    return 0;
}
