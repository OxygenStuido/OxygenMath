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
                for (size_t i = 0; i < N; ++i)
                {
                    for (size_t j = 0; j < N; ++j)
                    {
                        L(i, j) = (i == j) ? T::identity() : T::zero();
                    }
                }

                for (size_t i = 0; i < N; ++i)
                {
                    for (size_t j = 0; j < N; ++j)
                    {
                        U(i, j) = T::zero();
                        P(i, j) = T::zero();
                    }
                }
                for (size_t i = 0; i < N; ++i)
                {
                    P(i, i) = T::identity();
                }
            }
        };

        template <typename T, size_t N>
        LUPResult<T, N> LUPDecomposition(MatrixNM<T, N, N> &A)
        {
            LUPResult<T, N> result;
            result.swapCount = 0;
            result.isSingular = false;

            std::vector<size_t> pivot(N);
            for (size_t i = 0; i < N; ++i)
            {
                pivot[i] = i;
            }

            for (size_t k = 0; k < N; ++k)
            {
                size_t maxRow = k;
                T maxVal = A(k, k);
                T currentMax = (maxVal < T::zero()) ? -maxVal : maxVal;

                for (size_t i = k + 1; i < N; ++i)
                {
                    T val = A(i, k);
                    T absVal = (val < T::zero()) ? -val : val;
                    if (absVal > currentMax)
                    {
                        currentMax = absVal;
                        maxRow = i;
                    }
                }

                if (maxRow != k)
                {
                    for (size_t j = 0; j < N; ++j)
                    {
                        swap(A(k, j), A(maxRow, j));
                    }
                    std::swap(pivot[k], pivot[maxRow]);
                    result.swapCount++;
                }

                if (abs((A(k, k))) < Constants::epsilon)
                {
                    result.isSingular = true;
                }

                for (size_t j = k; j < N; ++j)
                {
                    T sum = T::zero();
                    for (size_t m = 0; m < k; ++m)
                    {
                        sum = sum + A(k, m) * A(m, j);
                    }
                    result.U(k, j) = A(k, j) - sum;
                }

                for (size_t i = k + 1; i < N; ++i)
                {
                    T sum = T::zero();
                    for (size_t m = 0; m < k; ++m)
                    {
                        sum = sum + A(i, m) * A(m, k);
                    }

                    T ukk = result.U(k, k);
                    if (abs(ukk) < Constants::epsilon)
                    {
                        A(i, k) = T::zero();
                    }
                    else
                    {
                        A(i, k) = (A(i, k) - sum) / ukk;
                    }
                    result.L(i, k) = A(i, k);
                }
            }

            MatrixNM<T, N, N> P_temp = MatrixNM<T, N, N>::identity();
            for (size_t step = 0; step < N; ++step)
            {
                if (pivot[step] != step)
                {
                    for (size_t j = 0; j < N; ++j)
                    {
                        std::swap(P_temp(step, j), P_temp(pivot[step], j));
                    }
                }
            }
            result.P = P_temp;

            return result;
        }

        template <typename T, size_t N>
        T determinant(const MatrixNM<T, N, N> &A_input)
        {
            MatrixNM<T, N, N> A = A_input;
            auto lup = LUPDecomposition(A);

            if (lup.isSingular)
            {
                return T::zero();
            }
            T detU = T::identity();
            for (size_t i = 0; i < N; ++i)
            {
                detU = detU * lup.U(i, i);
            }

            T sign = (lup.swapCount % 2 == 0) ? T::identity() : (T::zero() - T::identity());
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
    }

}