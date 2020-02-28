#ifndef TMATRIX_H
#define TMATRIX_H

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <random>
#include <iostream>

template<typename T, int _Col, int _Row>
class TMatrix
{
public:
    TMatrix()
    {
        Matrix = new Cell[_Row * _Col];
        for (size_t i = 0; i < _Row * _Col; ++i)
        {
            Matrix[i]._matrix = this;
            Matrix[i]._coord.A = i;
            Matrix[i]._coord.toXY();
        }
    }

    TMatrix(const TMatrix& M)
    {
        Matrix = new Cell[_Row * _Col];
        for (size_t i = 0; i < _Row * _Col; ++i)
        {
            Matrix[i].val = M.Matrix[i].val;
            Matrix[i]._matrix = this;
            Matrix[i]._coord.A = i;
            Matrix[i]._coord.toXY();
        }
    }

    ~TMatrix()
    {
        delete[] Matrix;
    }

    class Cell;
    friend class Cell;
    class Iterator;
    class const_Iterator;

    size_t count() const
    {
        return _Row * _Col;
    }

    std::pair<size_t, size_t> size()
    {
        return std::make_pair(_Row, _Col);
    }

    Cell& at(const int _x, const int _y)
    {
        coord.X = _x;
        coord.Y = _y;
        coord.toA();

        return Matrix[coord.A];
    }

    Cell get(const int _x, const int _y)
    {
        coord.X = _x;
        coord.Y = _y;
        coord.toA();

        return Matrix[coord.A];
    }

    Iterator begin()
    {
        return Iterator(this);
    }

    Iterator end()
    {
        return Iterator(this, count());
    }

    const_Iterator begin() const
    {
        return const_Iterator(this);
    }

    const_Iterator end() const
    {
        return const_Iterator(this, count());
    }

    const_Iterator cbegin() const
    {
        return const_Iterator(this);
    }
    const_Iterator cend() const
    {
        return const_Iterator(this, count());
    }
private:
    struct Coord;
public:
    class Cell
    {
    public:
        Cell() {}
        ~Cell() {}
        class Neighborhood_Iterator;
        friend class Neighborhood_Iterator;
        friend class TMatrix;

        T& value()
        {
          return val;
        }

        T value() const
        {
          return val;
        }

        std::pair<int,int> getCoordinates()
        {
            return std::make_pair(_coord.X, _coord.Y);
        }

        Neighborhood_Iterator begin()
        {
            return Neighborhood_Iterator(this);
        }

        Neighborhood_Iterator end()
        {
            return Neighborhood_Iterator(this, 8);
        }

        friend std::ostream& operator<< (std::ostream& out, const Cell& c)
        {
            out << c.val;
            return out;
        }

        bool operator==(Cell &c) const
        {
            return val == c.val;
        }

        bool operator!=(Cell &c) const
        {
            return val != c.val;
        }

        class Neighborhood_Iterator
        {
        public:
            Neighborhood_Iterator(Cell* C) : _cell(C), _aroundPos(0) {}
            Neighborhood_Iterator(Cell* C, size_t N) : _cell(C), _aroundPos(N) {}
            Neighborhood_Iterator(const Neighborhood_Iterator& it) {
                _cell = it._cell;
                _aroundPos = it._aroundPos;
            }

            ~Neighborhood_Iterator() {}

            Cell& operator*()
            {
                Coord c;
                c.X = _cell->_coord.X + Neighborhoods.at(_aroundPos).first;
                c.Y = _cell->_coord.Y + Neighborhoods.at(_aroundPos).second;
                c.toA();
                return (*_cell->_matrix)[c.A];
            }

            Cell* operator->()
            {
                return &(operator*());
            }

            Neighborhood_Iterator& operator++()
            {
                if (_aroundPos < 8)
                    ++ _aroundPos;
                return *this;
            }

            Neighborhood_Iterator& operator=(const Neighborhood_Iterator& n_it)
            {
                if (&n_it == this)
                    return *this;

                _cell = n_it._cell;
                _aroundPos = n_it._aroundPos;
                return *this;
            }

            bool operator==(const Neighborhood_Iterator& n_it) const
            {
                return (_cell == n_it._cell && _aroundPos == n_it._aroundPos);
            }

            bool operator!=(const Neighborhood_Iterator& n_it) const
            {
                return (_cell != n_it._cell || _aroundPos != n_it._aroundPos);
            }

        private:
            Cell* _cell;
            size_t _aroundPos;
            std::vector<std::pair<int, int>> Neighborhoods = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
        };

    private:
        T val;
        TMatrix* _matrix;
        TMatrix::Coord _coord;
    };

    class Iterator
    {
    public:
        Iterator(TMatrix* M) : _Matrix(M), _Pos(0) {}
        Iterator(TMatrix* M, const size_t N) : _Matrix(M), _Pos(N) {}
        Iterator(const Iterator& it)
        {
            _Matrix = it._Matrix;
            _Pos = it._Pos;
        }
        ~Iterator() {}

        Cell& operator*()
        {
            return (*_Matrix)[_Pos];
        }

        Cell* operator->()
        {
            return &(operator*());
        }

        Iterator& operator++()
        {
            ++_Pos;
            return *this;
        }

        Iterator& operator=(const Iterator& it)
        {
            if (&it == this)
                return *this;

            _Matrix = it._Matrix;
            _Pos = it._Pos;
            return *this;
        }
        bool operator==(const Iterator& it) const
        {
            return &((*_Matrix)[_Pos]) == &((*it._Matrix)[it._Pos]);
        }
        bool operator!=(const Iterator& it) const
        {
            return &((*_Matrix)[_Pos]) != &((*it._Matrix)[it._Pos]);
        }

    private:
        TMatrix* _Matrix;
        size_t _Pos;
    };

    class const_Iterator
    {
    public:
        const_Iterator(const TMatrix* M) : _Matrix(M), _Pos(0) {}
        const_Iterator(const TMatrix* M, const size_t N) : _Matrix(M), _Pos(N) {}
        const_Iterator(const const_Iterator& it)
        {
            _Matrix = it._Matrix;
            _Pos = it._Pos;
        }
        const_Iterator(const Iterator& it)
        {
            _Matrix = it._Matrix;
            _Pos = it._Pos;
        }
        ~const_Iterator() {}

        const Cell& operator*() const
        {
            return (*_Matrix)[_Pos];
        }

        const Cell* operator->() const
        {
            return &(operator*());
        }

        const_Iterator& operator++()
        {
            ++_Pos;
            return *this;
        }

        const_Iterator& operator=(const const_Iterator& it)
        {
            if (&it == this)
                return *this;

            _Matrix = it._Matrix;
            _Pos = it._Pos;
            return *this;
        }
        bool operator==(const const_Iterator& it) const
        {
            return &((*_Matrix)[_Pos]) == &((*it._Matrix)[it._Pos]);
        }
        bool operator!=(const const_Iterator& it) const
        {
            return &((*_Matrix)[_Pos]) != &((*it._Matrix)[it._Pos]);
        }

    private:
        const TMatrix* _Matrix;
        size_t _Pos;
    };

private:
    Cell* Matrix;
    Coord coord;

    Cell& operator[](const int A)
    {
        return *(Matrix + A);
    }
    const Cell& operator[](const int A) const
    {
        return *(Matrix + A);
    }

    struct Coord
    {
        int X;
        int Y;
        size_t A;

        void toA()
        {
            normalizeXY();
            A = _Col * X + Y;
        }

        void toXY()
        {
            if (A >= _Row * _Col)
                throw std::out_of_range("Field x or y");
            X = A / _Col;
            Y = A % _Col;
        }

        void normalizeXY()
        {
            if (X >= 0)
                X = X % _Row;
            else
                X = _Row + ((X % _Row) == 0 ? -_Row : (X % _Row));
            if (Y >= 0)
                Y = Y % _Col;
            else
                Y = _Col + ((Y % _Col) == 0 ? -_Col : (Y % _Col));
        }
    };
};


#endif // TMATRIX_H
