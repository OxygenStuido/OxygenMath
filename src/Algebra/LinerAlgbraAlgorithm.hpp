#pragma once
#include "AlgebraTool.hpp"
#include "MatrixNM.hpp"
#include "VectorN.hpp"
namespace OxygenMath
{
    namespace LinAlg
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
        /**
         * @brief 对给定的方阵进行LU分解（带部分主元的LUP分解）
         *
         * 该函数使用部分主元法对输入矩阵A进行LU分解，得到一个下三角矩阵L、
         * 上三角矩阵U以及行交换信息P，满足 PA = LU。
         *
         * @tparam T 矩阵元素的数据类型
         * @tparam N 矩阵的维度大小
         * @param A 输入的N×N方阵
         * @return LUPResult<T, N> 包含L、U、P矩阵以及是否奇异等信息的结果结构体
         */
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

        /**
         * 计算方阵的行列式值
         * 使用LU分解方法计算N×N矩阵的行列式
         * @param A_input 输入的N×N方阵
         * @return 矩阵的行列式值，如果矩阵奇异则返回0
         */
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

        /**
         * @brief 计算矩阵的行列式值
         * @param result LUP分解的结果，包含L、U矩阵以及相关的分解信息
         * @return 返回矩阵的行列式值，若矩阵奇异则返回0
         */
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

        /**
         * @brief 计算2x2矩阵的行列式
         *
         * @param A 输入的2x2矩阵
         * @return T 返回矩阵A的行列式值
         */
        template <typename T>
        T determinant(const MatrixNM<T, 2, 2> &A)
        {
            return A(0, 0) * A(1, 1) - A(0, 1) * A(1, 0);
        }

        /**
         * @brief 计算3x3矩阵的行列式
         *
         * 使用标准的3x3矩阵行列式计算公式，按第一行展开计算
         *
         * @param A_input 输入的3x3矩阵
         * @return T 返回计算得到的行列式值
         */
        template <typename T>
        T determinant(const MatrixNM<T, 3, 3> &A_input)
        {
            return A_input(0, 0) * (A_input(1, 1) * A_input(2, 2) - A_input(1, 2) * A_input(2, 1)) -
                   A_input(0, 1) * (A_input(1, 0) * A_input(2, 2) - A_input(1, 2) * A_input(2, 0)) +
                   A_input(0, 2) * (A_input(1, 0) * A_input(2, 1) - A_input(1, 1) * A_input(2, 0));
        }

        /**
         * @brief 计算4x4矩阵的行列式
         *
         * @param A 输入的4x4矩阵
         * @return T 矩阵的行列式值
         */
        template <typename T>
        T determinant(const MatrixNM<T, 4, 4> &A)
        {
            return A(0, 0) * (A(1, 1) * (A(2, 2) * A(3, 3) - A(2, 3) * A(3, 2)) - A(1, 2) * (A(2, 1) * A(3, 3) - A(2, 3) * A(3, 1)) + A(1, 3) * (A(2, 1) * A(3, 2) - A(2, 2) * A(3, 1))) -
                   A(0, 1) * (A(1, 0) * (A(2, 2) * A(3, 3) - A(2, 3) * A(3, 2)) - A(1, 2) * (A(2, 0) * A(3, 3) - A(2, 3) * A(3, 0)) + A(1, 3) * (A(2, 0) * A(3, 2) - A(2, 2) * A(3, 0))) +
                   A(0, 2) * (A(1, 0) * (A(2, 1) * A(3, 3) - A(2, 3) * A(3, 1)) - A(1, 1) * (A(2, 0) * A(3, 3) - A(2, 3) * A(3, 0)) + A(1, 3) * (A(2, 0) * A(3, 1) - A(2, 1) * A(3, 0))) -
                   A(0, 3) * (A(1, 0) * (A(2, 1) * A(3, 2) - A(2, 2) * A(3, 1)) - A(1, 1) * (A(2, 0) * A(3, 2) - A(2, 2) * A(3, 0)) + A(1, 2) * (A(2, 0) * A(3, 1) - A(2, 1) * A(3, 0)));
        }
        /**
         * @brief 计算方阵 A 的逆矩阵
         *
         * 使用 LU 分解方法计算给定方阵的逆矩阵。该方法通过求解一系列线性方程组 Ax = e_i，
         * 其中 e_i 是单位向量，来逐列构造逆矩阵。
         *
         * @param A 输入的 N×N 方阵
         * @return 返回 A 的逆矩阵
         * @throws std::runtime_error 如果矩阵 A 是奇异的（不可逆）
         */
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

        /**
         * @brief 计算矩阵的逆矩阵
         *
         * 该函数通过 LUP 分解结果求解原矩阵的逆。具体方法是：
         * 对于单位矩阵的每一列 e_i，求解线性方程 A * x = P * e_i，
         * 其中 A = L * U（LUP 分解结果），P 是置换矩阵。
         * 通过前向替换解 L * y = P * e_i，再通过后向替换解 U * x = y，
         * 得到的 x 即为逆矩阵的第 i 列。
         *
         * @param A LUP 分解结果，包含 L、U 矩阵和置换矩阵 P
         * @return MatrixNM<T, N, N> 原矩阵的逆矩阵
         * @throws std::runtime_error 如果矩阵奇异（不可逆）
         */
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

        /**
         * @brief 2x2矩阵的逆矩阵计算
         *
         * @param A 输入的2x2矩阵
         * @return MatrixNM<T, 2, 2> 逆矩阵
         */
        template <typename T>
        MatrixNM<T, 2, 2> inverse(const MatrixNM<T, 2, 2> &A)
        {
            T det = determinant(A);
            if (det == 0)
            {
                throw std::runtime_error("2x2 Matrix is singular.");
            }
            MatrixNM<T, 2, 2> inv;
            inv(0, 0) = A(1, 1);
            inv(0, 1) = -A(0, 1);
            inv(1, 0) = -A(1, 0);
            inv(1, 1) = A(0, 0);
            auto inv_det = T::identity() / det;
            inv = inv * inv_det;
            return inv;
        }

        /**
         * @brief 3x3矩阵的逆矩阵计算
         *
         * @param A 输入的3x3矩阵
         * @return MatrixNM<T, 3, 3> 逆矩阵
         */
        template <typename T>
        MatrixNM<T, 3, 3> inverse(const MatrixNM<T, 3, 3> &A)
        {
            T det = determinant(A);
            if (det == 0)
            {
                throw std::runtime_error("3x3 Matrix is singular.");
            }
            MatrixNM<T, 3, 3> inv;
            inv(0, 0) = (A(1, 1) * A(2, 2) - A(1, 2) * A(2, 1));
            inv(0, 1) = (A(0, 2) * A(2, 1) - A(0, 1) * A(2, 2));
            inv(0, 2) = (A(0, 1) * A(1, 2) - A(0, 2) * A(1, 1));
            inv(1, 0) = (A(1, 2) * A(2, 0) - A(1, 0) * A(2, 2));
            inv(1, 1) = (A(0, 0) * A(2, 2) - A(0, 2) * A(2, 0));
            inv(1, 2) = (A(0, 2) * A(1, 0) - A(0, 0) * A(1, 2));
            inv(2, 0) = (A(1, 0) * A(2, 1) - A(1, 1) * A(2, 0));
            inv(2, 1) = (A(0, 1) * A(2, 0) - A(0, 0) * A(2, 1));
            inv(2, 2) = (A(0, 0) * A(1, 1) - A(0, 1) * A(1, 0));
            auto inv_det = T::identity() / det;
            inv = inv * inv_det;
            return inv;
        }

        /**
         * @brief 高斯-赛德尔迭代法求解线性方程组 Ax = b
         * @param A 系数矩阵（N×N）
         * @param b 常数向量（N维）
         * @param x0 初始解（N维）
         * @param maxIter 最大迭代次数
         * @param tol 收敛容差
         * @return VectorN<T, N> 迭代得到的解
         */
        template <typename T, size_t N>
        VectorN<T, N> gaussSeidel(const MatrixNM<T, N, N> &A, const VectorN<T, N> &b,
                                  const VectorN<T, N> &x0, size_t maxIter = 1000, T tol = Constants::epsilon)
        {
            VectorN<T, N> x = x0;
            for (size_t iter = 0; iter < maxIter; ++iter)
            {
                VectorN<T, N> x_old = x;
                for (size_t i = 0; i < N; ++i)
                {
                    T sum = b(i);
                    for (size_t j = 0; j < N; ++j)
                    {
                        if (j != i)
                            sum -= A(i, j) * x(j);
                    }
                    x(i) = sum / A(i, i);
                }
                // 检查收敛
                T err = T::zero();
                for (size_t k = 0; k < N; ++k)
                    err += abs(x(k) - x_old(k));
                if (err < tol)
                    break;
            }
            return x;
        }

    }

}