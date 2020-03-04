#ifndef TMATRIXVIEW_H
#define TMATRIXVIEW_H

#include "TMatrix.h"

/* class MatrixView provide access to some part of TMatrix */
template<typename T, size_t _Col, size_t _Row>
class MatrixView : public TMatrix<T, _Col, _Row>
{
public:
    MatrixView(const TMatrix<T, _Col, _Row>& M, size_t c1, size_t c2)
        : TMatrix<T, _Col, _Row> (M) {
        border.start_col = c1;
        border.end_col = c2;
        border.start_row = 0;
        border.end_row = M.size().first;
    }
    MatrixView(TMatrix<T, _Col, _Row>& M, size_t c1, size_t c2)
        : TMatrix<T, _Col, _Row> (M) {
        border.start_col = c1;
        border.end_col = c2;
        border.start_row = 0;
        border.end_row = M.size().first;
    }
    ~MatrixView() {}

    class Iterator : public TMatrix<T, _Col, _Row>::Iterator
    {

    };

private:
struct Border {
        size_t start_col;
        size_t end_col;
        size_t start_row;
        size_t end_row;
    };
Border border;

};


#endif // TMATRIXVIEW_H
