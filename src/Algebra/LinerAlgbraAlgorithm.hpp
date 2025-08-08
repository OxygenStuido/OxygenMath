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
                // 1. 寻找主元
                size_t maxRow = k;
                for (size_t i = k + 1; i < N; ++i)
                {
                    if (abs(A_copy(i, k)) > abs(A_copy(maxRow, k)))
                        maxRow = i;
                }
                if (abs(A_copy(maxRow, k)) <= Constants::epsilon)
                {
                    result.isSingular = true;
                    return result;
                }

                // 2. 交换行（A、P、L的已知部分）
                if (maxRow != k)
                {
                    for (size_t j = 0; j < N; ++j)
                    {
                        swap(A_copy(k, j), A_copy(maxRow, j));
                        swap(result.P(k, j), result.P(maxRow, j));
                        if (j < k)
                            swap(result.L(k, j), result.L(maxRow, j)); // 只交换已知部分
                    }
                    result.swapCount++;
                }

                // 3. U的第k行
                for (size_t j = k; j < N; ++j)
                    result.U(k, j) = A_copy(k, j);

                // 4. L的第k列
                result.L(k, k) = 1; // 对角线始终为1
                for (size_t i = k + 1; i < N; ++i)
                {
                    result.L(i, k) = A_copy(i, k) / result.U(k, k);
                    for (size_t j = k; j < N; ++j)
                        A_copy(i, j) -= result.L(i, k) * result.U(k, j);
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

        template <typename T, size_t N>
        T determinant(const LUPResult<T, N> &result)
        {
            auto lup = result;
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

        template <typename T, size_t N>
        MatrixNM<T, N, N> inverse(const MatrixNM<T, N, N> &A)
        {
            auto lup = luDecomposition(A);
            if (lup.isSingular)
                throw std::runtime_error("Matrix is singular.");

            MatrixNM<T, N, N> inv;

            for (size_t col = 0; col < N; ++col)
            {
                // 单位向量 e
                MatrixNM<T, N, 1> e;
                for (size_t i = 0; i < N; ++i)
                    e(i, 0) = (i == col) ? T::identity() : T::zero();

                // 右端项 b = P * e
                MatrixNM<T, N, 1> b;
                b = lup.P * e;

                // 解 L*y = b（前向替换）
                MatrixNM<T, N, 1> y;
                for (size_t i = 0; i < N; ++i)
                {
                    T sum = b(i, 0);
                    for (size_t j = 0; j < i; ++j)
                        sum -= lup.L(i, j) * y(j, 0);
                    y(i, 0) = sum / lup.L(i, i);
                }

                // 解 U*x = y（后向替换）
                MatrixNM<T, N, 1> x;
                for (int i = N - 1; i >= 0; --i)
                {
                    T sum = y(i, 0);
                    for (size_t j = i + 1; j < N; ++j)
                        sum -= lup.U(i, j) * x(j, 0);
                    x(i, 0) = sum / lup.U(i, i);
                }

                for (size_t row = 0; row < N; ++row)
                    inv(row, col) = x(row, 0);
            }
            return inv;
        }
        template <typename T, size_t N>
        MatrixNM<T, N, N> inverse(const LUPResult<T, N> &A)
        {
            auto lup = A;
            if (lup.isSingular)
                throw std::runtime_error("Matrix is singular.");

            MatrixNM<T, N, N> inv;

            for (size_t col = 0; col < N; ++col)
            {
                // 单位向量 e
                MatrixNM<T, N, 1> e;
                for (size_t i = 0; i < N; ++i)
                    e(i, 0) = (i == col) ? T::identity() : T::zero();

                // 右端项 b = P * e
                MatrixNM<T, N, 1> b;
                b = lup.P * e;

                // 解 L*y = b（前向替换）
                MatrixNM<T, N, 1> y;
                for (size_t i = 0; i < N; ++i)
                {
                    T sum = b(i, 0);
                    for (size_t j = 0; j < i; ++j)
                        sum -= lup.L(i, j) * y(j, 0);
                    y(i, 0) = sum / lup.L(i, i);
                }

                // 解 U*x = y（后向替换）
                MatrixNM<T, N, 1> x;
                for (int i = N - 1; i >= 0; --i)
                {
                    T sum = y(i, 0);
                    for (size_t j = i + 1; j < N; ++j)
                        sum -= lup.U(i, j) * x(j, 0);
                    x(i, 0) = sum / lup.U(i, i);
                }

                for (size_t row = 0; row < N; ++row)
                    inv(row, col) = x(row, 0);
            }
            return inv;
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