#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "TMatrix.h"
#include "TPrint.h"

int main()
{
    std::cout << "Hello life!" << std::endl;

    srand(1567468);
    TMatrix< bool, 30, 15 > mat;
    for (auto &a : mat)
    {
        int k = rand();
        a = (bool)(k%2);
    }
    std::cout << std::endl;

    mat.print();
    std::cout << std::endl;

    TMatrix< bool, 30, 15 > mat1;
    auto life {[](auto it){
            bool t {false};
            int cnt {0};
            for (auto c : it)
            {
                if (c.value())
                    cnt++;
            }
            if (!it.value() && cnt == 3)
                t = true;
            else if (it.value() && (cnt == 2 || cnt == 3))
                t = true;
            else
                t = false;
            return t;
        }};

    mat1 = mat.calculate(life);
    mat = mat1;
    mat.print();
    std::cout << std::endl;

    return 0;
}
