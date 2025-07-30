#pragma once
#include <vector>
#include "NumberField.hpp"
#include "Vector.hpp"
#include "VectorN.hpp"
namespace OxygenMath
{
    template <typename T>
    class Matrix
    {
    private:
        Vector<T> data;
        size_t rows;
        size_t cols;
    public:
        Matrix(size_t rows, size_t cols)
            : data(rows * cols), rows(rows), cols(cols) {}
    };
}