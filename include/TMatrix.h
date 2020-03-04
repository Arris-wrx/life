#ifndef TMATRIX_H
#define TMATRIX_H

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <random>
#include <iostream>
#include <algorithm>

/**************************/
/* template class TMatrix */
/**************************/
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

    TMatrix(TMatrix&& M) : Matrix(M.Matrix)
    {
        for (size_t i = 0; i < _Row * _Col; ++i)
        {
            Matrix[i]._matrix = this;
        }

        M.Matrix = nullptr;
    }

    ~TMatrix()
    {
        delete[] Matrix;
    }

    class Cell;  // hidden class TMatrix::Cell, a wrapper on one cell of TMatrix
    friend class Cell;
    class Iterator; // TMatrix::Iterator
    class const_Iterator; //TMatrix::const_Iterator


    // return count of elements
    size_t count() const
    {
        return _Row * _Col;
    }

    // return pair of demensions <Row, Col>
    std::pair<size_t, size_t> size()
    {
        return std::make_pair(_Row, _Col);
    }

    // provide link to the Cell element of Matrix by coordinates (col, row)
    // impossible out of range
    Cell& at(const int _x, const int _y)
    {
        Coord c;
        c.X = _x;
        c.Y = _y;
        c.toA();

        return Matrix[c.A];
    }

    // return const element of Matrix by coordinates (col, row)
    // impossible out of range
    Cell get(const int _x, const int _y) const
    {
        Coord c;
        c.X = _x;
        c.Y = _y;
        c.toA();

        return Matrix[c.A];
    }

    // print Matrix
    void print() const
    {
        for (size_t i = 0; i < _Row; ++i)
        {
            for (size_t j = 0; j < _Col; ++j)
            {
                std::cout << (Matrix[_Col * i + j]).val << " ";
            }
            std::cout << std::endl;
        }
    }

    // assignment operator
    TMatrix& operator= (const TMatrix& M)
    {
        if (&M == this)
            return *this;

        delete[] Matrix;

        Matrix = new Cell[_Row * _Col];
        for (size_t i = 0; i < _Row * _Col; ++i)
        {
            Matrix[i].val = M.Matrix[i].val;
            Matrix[i]._matrix = this;
            Matrix[i]._coord.A = i;
            Matrix[i]._coord.toXY();
        }
        return *this;
    }

    // assignment move operator
    TMatrix& operator= (TMatrix&& M)
    {
        if (&M == this)
            return *this;

        delete[] Matrix;

        Matrix = M.Matrix;
        for (size_t i = 0; i < _Row * _Col; ++i)
        {
            Matrix[i]._matrix = this;
        }

        M.Matrix = nullptr;
        return *this;
    }

    // provide way to modifficate whole Matrix by the rule "foo"
    // Handler "foo" must return T
    // calculate returns new instance, original Matrix saved
    TMatrix calculate(T foo(const Cell& it))
    {
        TMatrix Dest;
        auto dest_it = Dest.begin();
        auto _oper{ [foo](const Cell& it) {
                Cell tmp;
                tmp.val = foo(it);
                return tmp;
                   }};
        std::transform(begin(), end(), dest_it, _oper);

        return Dest;
    }

    /* Iterations func */
    // return start position (0,0)
    Iterator begin()
    {
        return Iterator(this);
    }

    // return position after last (col, row)
    Iterator end()
    {
        return Iterator(this, count());
    }

    // return start position (0,0) const
    const_Iterator begin() const
    {
        return const_Iterator(this);
    }

    // return position after last (col, row) const
    const_Iterator end() const
    {
        return const_Iterator(this, count());
    }

    // return start position (0,0) const
    const_Iterator cbegin() const
    {
        return const_Iterator(this);
    }

    // return position after last (col, row) const
    const_Iterator cend() const
    {
        return const_Iterator(this, count());
    }
private:
    struct Coord;  // for calculating. Not for storage
public:
    /********************************************
     * Class Cell
     * hidden class provides access to Matrix cell
     *********************************************/
    class Cell
    {
    public:
        ~Cell() {}
        class Neighborhood_Iterator;
        class const_Neighborhood_Iterator;

        friend class Neighborhood_Iterator;
        friend class const_Neighborhood_Iterator;
        friend class TMatrix;

        T& value()
        {
          return val;
        }

        T value() const
        {
          return val;
        }

        // return coordinates of this Cell
        std::pair<int,int> getCoordinates()
        {
            return std::make_pair(_coord.X, _coord.Y);
        }

        /* Iterations func */

        Neighborhood_Iterator begin()
        {
            return Neighborhood_Iterator(this);
        }

        Neighborhood_Iterator end()
        {
            return Neighborhood_Iterator(this, 8);
        }

        const_Neighborhood_Iterator begin() const
        {
            return const_Neighborhood_Iterator(this);
        }

        const_Neighborhood_Iterator end() const
        {
            return const_Neighborhood_Iterator(this, 8);
        }

        const_Neighborhood_Iterator cbegin() const
        {
            return const_Neighborhood_Iterator(this);
        }

        const_Neighborhood_Iterator cend() const
        {
            return const_Neighborhood_Iterator(this, 8);
        }

        // translate Cell to out stream as type T
        friend std::ostream& operator<< (std::ostream& out, const Cell& c)
        {
            out << c.val;
            return out;
        }

        // assignment operator
        Cell& operator= (const Cell& c)
        {
            if (&c == this)
                return *this;

            val = c.val;
        }

        // assignment operator for type T
        Cell& operator= (const T t)
        {
            if (t == this->val)
                return *this;

            val = t;
        }

        bool operator==(Cell &c) const
        {
            return val == c.val;
        }

        bool operator!=(Cell &c) const
        {
            return val != c.val;
        }

        /*
         * Iterator by neighborhoods cells
         */
        class Neighborhood_Iterator
        {
        public:
            Neighborhood_Iterator(Cell* C) : _cell(C), _aroundPos(0) {}
            Neighborhood_Iterator(Cell* C, const size_t N) : _cell(C), _aroundPos(N) {}
            Neighborhood_Iterator(const Neighborhood_Iterator& it) {
                _cell = it._cell;
                _aroundPos = it._aroundPos;
            }

            ~Neighborhood_Iterator() {}

            Cell& operator*()
            {
                // calculate shift
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

                _cell->val = n_it._cell->val;
                _cell->_coord = n_it._cell->_coord;
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
            Cell* _cell;  // pointer to source cell
            size_t _aroundPos; // current shift position
            std::vector<std::pair<int, int>> Neighborhoods = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };  // vector of shift coordinates rule
        };

        /*
         * Const Iterator by neighborhoods cells
         */
        class const_Neighborhood_Iterator
        {
        public:
            const_Neighborhood_Iterator(const Cell* C) : _cell(C), _aroundPos(0) {}
            const_Neighborhood_Iterator(const Cell* C, const size_t N) : _cell(C), _aroundPos(N) {}
            const_Neighborhood_Iterator(const const_Neighborhood_Iterator& it) {
                _cell = it._cell;
                _aroundPos = it._aroundPos;
            }
            const_Neighborhood_Iterator(const Neighborhood_Iterator& it) {
                _cell = it._cell;
                _aroundPos = it._aroundPos;
            }

            ~const_Neighborhood_Iterator() {}

            const Cell& operator*() const
            {
                Coord c;
                c.X = _cell->_coord.X + Neighborhoods.at(_aroundPos).first;
                c.Y = _cell->_coord.Y + Neighborhoods.at(_aroundPos).second;
                c.toA();
                return (*_cell->_matrix)[c.A];
            }

            const Cell* operator->() const
            {
                return &(operator*());
            }

            const_Neighborhood_Iterator& operator++()
            {
                if (_aroundPos < 8)
                    ++ _aroundPos;
                return *this;
            }

            const_Neighborhood_Iterator& operator=(const const_Neighborhood_Iterator& n_it)
            {
                if (&n_it == this)
                    return *this;

                _cell->val = n_it._cell->val;
                _cell->_coord = n_it._cell->_coord;
                _aroundPos = n_it._aroundPos;
                return *this;
            }

            bool operator==(const const_Neighborhood_Iterator& n_it) const
            {
                return (_cell == n_it._cell && _aroundPos == n_it._aroundPos);
            }

            bool operator!=(const const_Neighborhood_Iterator& n_it) const
            {
                return (_cell != n_it._cell || _aroundPos != n_it._aroundPos);
            }

        private:
            const Cell* _cell;
            size_t _aroundPos;
            std::vector<std::pair<int, int>> Neighborhoods = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
        };

    private:
        Cell() : _matrix(nullptr) {} // hidden cell constructor

        T val; // Cell value
        TMatrix* _matrix; // pointer to cell holder
        TMatrix::Coord _coord; // cell coordinates
    };

    /*******************************************
     *  TMatrix::Iterator standart iterator
     * *****************************************/
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
        TMatrix* _Matrix; // pointer to object holder
        size_t _Pos; // current iterator position
    };

    /****************************************************
     *  TMatrix::const_Iterator standart const iterator
     * *************************************************/
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
        const TMatrix* _Matrix;  // pointer to object holder
        size_t _Pos; // current iterator position
    };

private:
    Cell* Matrix; // main pointer to array

    Cell& operator[](const int A)
    {
        return *(Matrix + A);
    }

    const Cell& operator[](const int A) const
    {
        return *(Matrix + A);
    }

    // stuct Coord only for translate from two demensions coordinates to one demensions and back
    // and using unlimited coordinates for  ciclic borders
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
