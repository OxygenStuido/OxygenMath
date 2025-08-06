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
    /*! \brief 矩阵模板类，支持基本线性代数运算,只实现矩阵的构造和基本运算，求解行列式，逆，是否奇异位于LinerAlgbraAlgorithm.hpp
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

        static MatrixNM<T, Rows, Cols> identity()
        {
            static_assert(Rows == Cols, "Identity matrix must be square");
            MatrixNM<T, Rows, Cols> result;
            for (size_t i = 0; i < Rows; ++i)
            {
                result(i, i) = T::identity();
            }
            return result;
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
    template <typename T>
    class MatrixNM<T, 2, 2> : public MatrixBase<MatrixNM<T, 2, 2>>
    {
        static_assert(std::is_base_of<NumberField<T>, T>::value,
                      "Matrix<T> requires T to inherit from NumberField<T>");

    private:
        T data[4];

    public:
        MatrixNM() : data{T::zero(), T::zero(), T::zero(), T::zero()} {}

        MatrixNM(const std::initializer_list<std::initializer_list<T>> &init)
        {
            if (init.size() != 2 || (init.size() > 0 && init.begin()->size() != 2))
                throw std::invalid_argument("Initializer list size does not match 2x2 matrix dimensions");

            auto row1 = *init.begin();
            auto row2 = *(init.begin() + 1);

            data[0] = *(row1.begin());
            data[1] = *(row1.begin() + 1);
            data[2] = *(row2.begin());
            data[3] = *(row2.begin() + 1);
        }

        MatrixNM(T m11, T m12, T m21, T m22) : data{m11, m12, m21, m22} {}

        T &operator()(size_t row, size_t col)
        {
            return data[row * 2 + col];
        }

        const T &operator()(size_t row, size_t col) const
        {
            return data[row * 2 + col];
        }

        size_t rows() const { return 2; }
        size_t cols() const { return 2; }

        static MatrixNM<T, 2, 2> identity()
        {
            MatrixNM<T, 2, 2> result;
            for (size_t i = 0; i < 2; ++i)
            {
                result(i, i) = T::identity();
            }
            return result;
        }

        // MatrixNM inverse() const
        // {
        //     T det = determinant();
        //     if (det == T::zero())
        //     {
        //         throw std::runtime_error("Matrix is singular and cannot be inverted");
        //     }
        //     T inv_det = T::identity() / det;
        //     return MatrixNM(
        //         data[3] * inv_det, -data[1] * inv_det,
        //         -data[2] * inv_det, data[0] * inv_det);
        // }

        template <typename Expr>
        MatrixNM &operator=(const Expr &expr)
        {
            data[0] = expr(0, 0);
            data[1] = expr(0, 1);
            data[2] = expr(1, 0);
            data[3] = expr(1, 1);
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const MatrixNM &matrix)
        {
            return os << "[[" << matrix(0, 0) << ", " << matrix(0, 1) << "],\n"
                      << " [" << matrix(1, 0) << ", " << matrix(1, 1) << "]]";
        }
    };

    template <typename T>
    class MatrixNM<T, 3, 3> : public MatrixBase<MatrixNM<T, 3, 3>>
    {
        static_assert(std::is_base_of<NumberField<T>, T>::value,
                      "Matrix<T> requires T to inherit from NumberField<T>");

    private:
        T data[9];

    public:
        MatrixNM() : data{T::zero(), T::zero(), T::zero(),
                          T::zero(), T::zero(), T::zero(),
                          T::zero(), T::zero(), T::zero()} {}

        MatrixNM(const std::initializer_list<std::initializer_list<T>> &init)
        {
            if (init.size() != 3 || (init.size() > 0 && init.begin()->size() != 3))
                throw std::invalid_argument("Initializer list size does not match 3x3 matrix dimensions");

            auto it = init.begin();
            for (size_t i = 0; i < 3; ++i, ++it)
            {
                auto row = *it;
                auto row_it = row.begin();
                for (size_t j = 0; j < 3; ++j, ++row_it)
                {
                    data[i * 3 + j] = *row_it;
                }
            }
        }

        MatrixNM(T m11, T m12, T m13,
                 T m21, T m22, T m23,
                 T m31, T m32, T m33)
            : data{m11, m12, m13,
                   m21, m22, m23,
                   m31, m32, m33} {}

        T &operator()(size_t row, size_t col)
        {
            return data[row * 3 + col];
        }

        const T &operator()(size_t row, size_t col) const
        {
            return data[row * 3 + col];
        }

        size_t rows() const { return 3; }
        size_t cols() const { return 3; }

        static MatrixNM<T, 3, 3> identity()
        {
            MatrixNM<T, 3, 3> result;
            for (size_t i = 0; i < 3; ++i)
            {
                result(i, i) = T::identity();
            }
            return result;
        }

        // MatrixNM inverse() const
        // {
        //     T det = determinant();
        //     if (det == T::zero())
        //     {
        //         throw std::runtime_error("Matrix is singular and cannot be inverted");
        //     }
        //     T inv_det = T::identity() / det;

        //     return MatrixNM(
        //         (data[4] * data[8] - data[5] * data[7]) * inv_det,
        //         (data[2] * data[7] - data[1] * data[8]) * inv_det,
        //         (data[1] * data[5] - data[2] * data[4]) * inv_det,

        //         (data[5] * data[6] - data[3] * data[8]) * inv_det,
        //         (data[0] * data[8] - data[2] * data[6]) * inv_det,
        //         (data[2] * data[3] - data[0] * data[5]) * inv_det,

        //         (data[3] * data[7] - data[4] * data[6]) * inv_det,
        //         (data[1] * data[6] - data[0] * data[7]) * inv_det,
        //         (data[0] * data[4] - data[1] * data[3]) * inv_det);
        // }

        template <typename Expr>
        MatrixNM &operator=(const Expr &expr)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    data[i * 3 + j] = expr(i, j);
                }
            }
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const MatrixNM &matrix)
        {
            return os << "[[" << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << "],\n"
                      << " [" << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << "],\n"
                      << " [" << matrix(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << "]]";
        }
    };
}