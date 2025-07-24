#pragma once
#include <vector>
#include "NumberField.hpp"
namespace OxygenMath
{
    template<typename T>
    class Matrix
    {
    public:
        Matrix() : row_size(0), col_size(0),data(0) {
           
        }
        Matrix(size_t row, size_t col) : row_size(row), col_size(col), data(row * col) {
            
        }
        
    private:
        size_t row_size;
        size_t col_size;
        std::vector<NumberField<T>> data;
    };
}