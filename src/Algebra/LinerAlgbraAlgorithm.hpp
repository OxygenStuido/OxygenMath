#pragma once
#include "AlgebraTool.hpp"
#include "MatrixNM.hpp"
namespace OxygenMath
{
    namespace linalg
    {
        template <typename T, size_t N>
        struct LUPResult
        {
            MatrixNM<T, N, N> L;
            MatrixNM<T, N, N> U;
            MatrixNM<T, N, N> P;
            int swapCount;
            bool isSingular;

            LUPResult() : swapCount(0), isSingular(false)
            {
                // 初始化L为单位矩阵，U和P为零矩阵
                for (size_t i = 0; i < N; ++i)
                {
                    for (size_t j = 0; j < N; ++j)
                    {
                        L(i, j) = (i == j) ? 1 : 0;
                        U(i, j) = 0;
                        P(i, j) = (i == j) ? 1 : 0;
                    }
                }
            }
        };

        template <typename T, size_t N>
        LUPResult<T, N> luDecomposition(const MatrixNM<T, N, N> &A)
        {
            LUPResult<T, N> result;
            MatrixNM<T, N, N> A_copy = A;
            for (size_t k = 0; k < N; ++k)
            {
                // 寻找当前列中最大值的行索引
                size_t maxRow = k;
                for (size_t i = k + 1; i < N; ++i)
                {
                    if (abs(A_copy(i, k)) > abs(A_copy(maxRow, k)))
                    {
                        maxRow = i;
                    }
                }
                // 如果最大值为0，矩阵是奇异的
                if (A_copy(maxRow, k) <= Constants::epsilon)
                {
                    result.isSingular = true;
                    return result;
                }

                // 交换行
                if (maxRow != k)
                {
                    for (size_t j = 0; j < N; ++j)
                    {
                        swap(A_copy(k, j), A_copy(maxRow, j));
                        swap(result.P(k, j), result.P(maxRow, j));
                    }
                    result.swapCount++;
                }

                // 计算U的第k行
                for (size_t j = k; j < N; ++j)
                {
                    result.U(k, j) = A_copy(k, j);
                }

                // 计算L的第k列
                for (size_t i = k + 1; i < N; ++i)
                {
                    result.L(i, k) = A_copy(i, k) / A_copy(k, k);
                    for (size_t j = k; j < N; ++j)
                    {
                        A_copy(i, j) -= result.L(i, k) * result.U(k, j);
                    }
                }
            }
            return result;
        }

        template <typename T, size_t N>
        T determinant(const MatrixNM<T, N, N> &A_input)
        {
            MatrixNM<T, N, N> A = A_input;
            auto lup = luDecomposition(A);

            if (lup.isSingular)
            {
                return 0;
            }

            T detU = 1;
            for (size_t i = 0; i < N; ++i)
            {
                detU *= lup.U(i, i);
            }

            T sign = (lup.swapCount % 2 == 0) ? 1 : -1;
            return sign * detU;
        }
        template <typename T>
        T determinant(const MatrixNM<T, 2, 2> &A)
        {
            return A(0, 0) * A(1, 1) - A(0, 1) * A(1, 0);
        }

        template <typename T>
        T determinant(const MatrixNM<T, 3, 3> &A_input)
        {
            return A_input(0, 0) * (A_input(1, 1) * A_input(2, 2) - A_input(1, 2) * A_input(2, 1)) -
                   A_input(0, 1) * (A_input(1, 0) * A_input(2, 2) - A_input(1, 2) * A_input(2, 0)) +
                   A_input(0, 2) * (A_input(1, 0) * A_input(2, 1) - A_input(1, 1) * A_input(2, 0));
        }

        template <typename T>
        MatrixNM<T, 2, 2> inverse(const MatrixNM<T, 2, 2> &A)
        {
            T det = determinant(A);
            if (det == 0)
            {
                throw std::runtime_error("2x2 Matrix is singular.");
            }
            MatrixNM<T, 2, 2> inv;
            inv(0, 0) = A(1, 1) / det;
            inv(0, 1) = -A(0, 1) / det;
            inv(1, 0) = -A(1, 0) / det;
            inv(1, 1) = A(0, 0) / det;
            return inv;
        }

        template <typename T>
        MatrixNM<T, 3, 3> inverse(const MatrixNM<T, 3, 3> &A)
        {
            T det = determinant(A);
            if (det == 0)
            {
                throw std::runtime_error("3x3 Matrix is singular.");
            }
            MatrixNM<T, 3, 3> inv;
            inv(0, 0) = (A(1, 1) * A(2, 2) - A(1, 2) * A(2, 1)) / det;
            inv(0, 1) = (A(0, 2) * A(2, 1) - A(0, 1) * A(2, 2)) / det;
            inv(0, 2) = (A(0, 1) * A(1, 2) - A(0, 2) * A(1, 1)) / det;
            inv(1, 0) = (A(1, 2) * A(2, 0) - A(1, 0) * A(2, 2)) / det;
            inv(1, 1) = (A(0, 0) * A(2, 2) - A(0, 2) * A(2, 0)) / det;
            inv(1, 2) = (A(0, 2) * A(1, 0) - A(0, 0) * A(1, 2)) / det;
            inv(2, 0) = (A(1, 0) * A(2, 1) - A(1, 1) * A(2, 0)) / det;
            inv(2, 1) = (A(0, 1) * A(2, 0) - A(0, 0) * A(2, 1)) / det;
            inv(2, 2) = (A(0, 0) * A(1, 1) - A(0, 1) * A(1, 0)) / det;
            return inv;
        }
    }

}