#ifndef TMATRIXVIEW_H
#define TMATRIXVIEW_H

#include "TMatrix.h"

/* class MatrixView provide access to some part of TMatrix */
template<typename T, size_t _Col, size_t _Row>
class MatrixView
{
public:

    MatrixView(TMatrix<T, _Col, _Row>& M, size_t c1, size_t c2)
        : Mat (M) {
        border.start_col = c1 < 0 ? 0 : c1;
        border.end_col = c2 > _Col ? _Col : c2;
        border.start_row = 0;
        border.end_row = M.size().first;
    }

    MatrixView(TMatrix<T, _Col, _Row>& M, size_t c1, size_t c2, size_t r1, size_t r2)
        : Mat (M) {
        border.start_col = c1 < 0 ? 0 : c1;
        border.end_col = c2 > _Col ? _Col : c2;
        border.start_row = r1 < 0 ? 0 : r1;
        border.end_row = r2 > _Row ? _Row : r2;
    }

    ~MatrixView() {}

    // return count of elements
    size_t count() const
    {
        return (border.end_row - border.start_row) * (border.end_col - border.start_col);
    }

    // return pair of demensions <Row, Col>
    std::pair<size_t, size_t> size()
    {
        return std::make_pair((border.end_row - border.start_row), (border.end_col - border.start_col));
    }

    // print view
    void print() const
    {
        for (size_t i = border.start_row; i < border.end_row; ++i)
        {
            for (size_t j = border.start_col; j < border.end_col; ++j)
            {
                std::cout << Mat.get(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

    // provide link to the Cell element of View by it's coordinates (col, row)
    // impossible out of range
    typename TMatrix<T, _Col, _Row>::Cell& at(const int _x, const int _y)
    {
        int x, y;
        if (_x >= 0)
            x = _x % size().first;
        else
        {
            int div_x = std::div(_x, size().first).rem;
            x = size().first + (div_x == 0 ? -size().first : div_x);
        }
        if (_y >= 0)
            y = _y % size().second;
        else
        {
            int div_y = std::div(_y, size().second).rem;
            y = size().second + (div_y == 0 ? -size().second : div_y);
        }

        x += border.start_row;
        y += border.start_col;

        return Mat.at(x, y);
    }

private:
struct Border {
        size_t start_col;
        size_t end_col;
        size_t start_row;
        size_t end_row;
    };
Border border;

TMatrix<T, _Col, _Row>& Mat;

};


#endif // TMATRIXVIEW_H
