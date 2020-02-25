#ifndef CELL_H
#define CELL_H

#include <random>

class Cell
{
public:
    bool state;
    Cell (bool state) : state(state) {}
    Cell () { rand(); }
    ~Cell() {}

    bool rnd()
    {
        srand(1234);
        state = static_cast<bool>(rand()%2);
        return state;
    }

    friend std::ostream& operator<< (std::ostream &out, const Cell &cell);
};

#endif // CELL_H

