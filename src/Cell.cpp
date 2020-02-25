#include "Cell.h"

bool operator== (const Cell& c1, const Cell& c2)
{
    return c1.state == c2.state;
}

std::ostream& operator<< (std::ostream &out, const Cell &c)
{
    int st = int(c.state);
    out << st;
    return out;
}
