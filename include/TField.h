#ifndef TFIELD_H
#define TFIELD_H

#include <cstdlib>
#include <stdexcept>

template<class T, int x, int y>
class TField
{
private:
    T* Field;

public:
    TField()
    {
        Field = new T[x*y];
    }

    ~TField()
    {
        delete Field;
    }

    int size()
    {
        return x*y;
    }
    T& operator[](const int index)
    {
        if (index >= 0)
            return *(Field + index);
        else
            return *(Field + (size() + index));
    }

    T& operator()(const int row, const int column)
    {
        if (row >= abs(y) || column >= abs (x) )
            throw std::out_of_range("Field x or y");

        T* Row = nullptr;
        if (row >= 0)
            Row = Field + (x * row);
        else
            Row = Field + (x * (y + row));

        if (column >=0)
            return *(Row + column);
        else
            return *(Row + (x + column));
    }

    class Iterator
    {
        TField* _Field;
        int _pos;
    public:

        Iterator(TField* field) : _Field(field), _pos(0) {}
        Iterator(TField* field, int s_pos) : _Field(field), _pos(s_pos) {}

        T& operator*()
        {
            return (*_Field)[_pos];
        }
        T* operator->()
        {
            return &(operator*());
        }
        Iterator& operator++()
        {
            ++_pos;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp(this);
            ++(*this);
            return tmp;
        }
        Iterator operator+(int n)
        {
            Iterator tmp(this);
            tmp._pos += n;
            return tmp;
        }
        Iterator& operator+=(int n)
        {
            _pos += n;
            return *this;
        }
        bool operator==(const Iterator& other)
        {
            return &((*_Field)[_pos]) == &((*other._Field)[other._pos]);
        }
        bool operator!=(const Iterator& other)
        {
            return &((*_Field)[_pos]) != &((*other._Field)[other._pos]);
        }

    };
    Iterator begin()
    {
        return Iterator(this);
    }
    Iterator end()
    {
        return Iterator(this, size());
    }

    class AroundIterator
    {
        TField* _Field;
        int _Center;
        int _pos;
    public:
        AroundIterator(TField* field, int center) : _Field(field), _Center(center), _pos(0) {}
        AroundIterator(TField* field, int center, int pos) : _Field(field), _Center(center), _pos(pos) {}

        T& operator*()
        {
            T tmp;
            switch (_pos) {
            case 1:
                (*_Field)[_pos];
                break;
            default:
                break;
            }

            return *tmp;
        }
        T* operator->()
        {
            return &(operator*());
        }
    };
    AroundIterator Abegin()
    {
        return Iterator(this);
    }
    AroundIterator Aend()
    {
        return Iterator(this, size());
    }
};

#endif // TFIELD_H
