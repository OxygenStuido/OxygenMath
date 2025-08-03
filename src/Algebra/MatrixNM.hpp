#pragma once
#include <vector>
#include <stdexcept>
#include <ostream>
#include "VectorN.hpp"
#include "NumberField.hpp"
#include "AlgebraTool.hpp"
#include "MatrixBase.hpp"
#include "MatrixExpr.hpp"
#include "../Constants.hpp"

namespace OxygenMath
{
    /*! \brief 矩阵模板类，支持基本线性代数运算
     * \tparam T 矩阵元素类型，必须继承自NumberField
     */
    template <typename T, size_t Rows, size_t Cols>
    class MatrixNM : public MatrixBase<MatrixNM<T, Rows, Cols>>
    {
        static_assert(std::is_base_of<NumberField<T>, T>::value,
                      "Matrix<T> requires T to inherit from NumberField<T>");

    private:
        std::vector<T> data;
        using Scalar = T;

    public:
        MatrixNM() : data(Rows * Cols, T::zero()) {}

        MatrixNM(const std::initializer_list<std::initializer_list<T>> &init)
        {
            if (init.size() != Rows || (init.size() > 0 && init.begin()->size() != Cols))
                throw std::invalid_argument("Initializer list size does not match matrix dimensions");

            data.reserve(Rows * Cols);
            for (const auto &row : init)
            {
                for (const auto &elem : row)
                {
                    data.push_back(elem);
                }
            }
        }

        T &operator()(size_t row, size_t col)
        {
            return data[row * Cols + col];
        }

        const T &operator()(size_t row, size_t col) const
        {
            return data[row * Cols + col];
        }

        size_t rows() const { return Rows; }
        size_t cols() const { return Cols; }

        // 从表达式赋值
        template <typename Expr>
        MatrixNM &operator=(const Expr &expr)
        {
            std::vector<T> tmp(Rows * Cols);
            for (size_t i = 0; i < Rows; ++i)
                for (size_t j = 0; j < Cols; ++j)
                    tmp[i * Cols + j] = expr(i, j);
            data = std::move(tmp);
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const MatrixNM &matrix)
        {
            if (Rows == 0 || Cols == 0)
            {
                return os << "[]";
            }

            os << "[";
            for (size_t i = 0; i < Rows; ++i)
            {
                if (i != 0)
                    os << " "; 

                os << "[";
                for (size_t j = 0; j < Cols; ++j)
                {
                    os << matrix(i, j);
                    if (j < Cols - 1)
                    {
                        os << ", ";
                    }
                }
                os << "]";

                if (i < Rows - 1)
                {
                    os << ",\n";
                }
            }
            return os << "]";
        }
    };
}