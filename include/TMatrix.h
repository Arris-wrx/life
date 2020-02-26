#ifndef TMATRIX_H
#define TMATRIX_H

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <random>

template<typename T, int _Y, int _X>
class TMatrix
{
public:
    TMatrix()
    {
        Matrix = new Cell[_X * _Y];
    }

    ~TMatrix()
    {
        delete[] Matrix;
    }

    class Cell;
    class Iterator;
    class const_Iterator;

    size_t count()
    {
        return _X * _Y;
    }

    std::pair<size_t, size_t> size()
    {
        return std::make_pair(_X, _Y);
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

    const_Iterator cbegin() const
    {
        return const_Iterator(this);
    }
    const_Iterator cend() const
    {
        return const_Iterator(this, count());
    }

    class Cell
    {
    public:
        Cell(T t) : val(t) {}
        Cell() {}
        ~Cell() {}
        class Neighborhood_Iterator;

        T& value()
        {
          return val;
        }

        class Neighborhood_Iterator
        {
        public:
            Neighborhood_Iterator() {}

        private:
            Cell* _cell;
            std::vector<std::pair<int, int>> Neighborhoods = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
        };

    private:
        T val;
        int __X, __Y;
    };

    class Iterator
    {
    public:
        Iterator(TMatrix* M) : _Matrix(M), _Pos(0) {}
        Iterator(TMatrix* M, size_t N) : _Matrix(M), _Pos(N) {}
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
        const_Iterator(const TMatrix* M, size_t N) : _Matrix(M), _Pos(N) {}
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

        Cell& operator*() const
        {
            return (*_Matrix)[_Pos];
        }

        Cell* operator->() const
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
    struct Coord;
    Cell* Matrix;
    Coord coord;
    Cell& operator[](const int A)
    {
        return *(Matrix + A);
    }
    Cell& operator[](const int A) const
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
            A = _Y * X + Y;
        }

        void toXY()
        {
            if (A >= _X * _Y)
                throw std::out_of_range("Field x or y");
            X = A % _X;
            Y = A / _Y;
        }

        void normalizeXY()
        {
            if (X >= 0)
                X = X % _X;
            else
                X = _X + ((X % _X) == 0 ? -_X : (X % _X));
            if (Y >= 0)
                Y = Y % _Y;
            else
                Y = _Y + ((Y % _Y) == 0 ? -_Y : (Y % _Y));
        }
    };
};

#endif // TMATRIX_H
