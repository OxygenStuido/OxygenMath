#pragma once
#include <vector>
#include <stdexcept>
#include <ostream>
#include "Vector.hpp"
#include "VectorN.hpp"
#include "NumberField.hpp"
#include "AlgebraTool.hpp"
#include "../Constants.hpp"

namespace OxygenMath
{
    /*! \brief 矩阵模板类，支持基本线性代数运算
     * \tparam T 矩阵元素类型，必须继承自NumberField
     */
    template <typename T, size_t Rows, size_t Cols>
    class MatrixNM
    {
        static_assert(std::is_base_of<NumberField<T>, T>::value,
                      "Matrix<T> requires T to inherit from NumberField<T>");

    private:
        std::vector<T> data;

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

        // 矩阵加法
        MatrixNM operator+(const MatrixNM &other) const
        {
            MatrixNM result;
            for (size_t i = 0; i < Rows * Cols; ++i)
            {
                result.data[i] = this->data[i] + other.data[i];
            }
            return result;
        }

        // 矩阵减法
        MatrixNM operator-(const MatrixNM &other) const
        {
            MatrixNM result;
            for (size_t i = 0; i < Rows * Cols; ++i)
            {
                result.data[i] = this->data[i] - other.data[i];
            }
            return result;
        }

        // 矩阵乘法
        template <size_t OtherCols>
        MatrixNM<T, Rows, OtherCols> operator*(const MatrixNM<T, Cols, OtherCols> &other) const
        {
            MatrixNM<T, Rows, OtherCols> result;
            for (size_t i = 0; i < Rows; ++i)
            {
                for (size_t k = 0; k < Cols; ++k)
                {
                    T val = (*this)(i, k); // 缓存左矩阵元素
                    for (size_t j = 0; j < OtherCols; ++j)
                    {
                        result(i, j) += val * other(k, j); // 连续访问右矩阵
                    }
                }
            }
            return result;
        }

        // 输出矩阵到流
        friend std::ostream &operator<<(std::ostream &os, const MatrixNM &matrix)
        {
            for (size_t i = 0; i < Rows; ++i)
            {
                os << "[ ";
                for (size_t j = 0; j < Cols; ++j)
                {
                    os << matrix(i, j);
                    if (j < Cols - 1)
                        os << ", ";
                }
                os << " ]\n";
            }
            return os;
        }
    };
}