#ifndef MATRIXVIEW_H
#define MATRIXVIEW_H

#include "TMatrix.h"

/* class MatrixView provide access to some part of TMatrix */
template<typename T>
class MatrixView
{
public:
    MatrixView() {}
    ~MatrixView() {}

    MatrixView operator= (const MatrixView);
private:
    TMatrix<T, int, int>& Host;
    struct
    {

    }
};

#endif // MATRIXVIEW_H
