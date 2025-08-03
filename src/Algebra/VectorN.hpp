#pragma once
#include <array>
#include <stdexcept>
#include "MatrixBase.hpp"
#include "MatrixExpr.hpp"
#include "AlgebraTool.hpp"

namespace OxygenMath
{
    template <typename T, size_t N>
    class VectorN : public MatrixBase<VectorN<T, N>>
    {
    private:
        std::array<T, N> data;
        bool is_row_vector = false; // 默认是列向量
    public:
        VectorN() : data{}
        {
            for (size_t i = 0; i < N; ++i)
                data[i] = T::zero();
        }

        VectorN(std::initializer_list<T> init)
        {
            if (init.size() != N)
                throw std::invalid_argument("Initializer list size does not match vector dimension");

            std::copy(init.begin(), init.end(), data.begin());
        }

        T &operator()(size_t i, size_t j = 0)
        {
            if (j != 0 || i >= N)
                throw std::out_of_range("Vector index out of range");
            return data[i];
        }

        const T &operator()(size_t i, size_t j = 0) const
        {
            if (j != 0 || i >= N)
                throw std::out_of_range("Vector index out of range");
            return data[i];
        }

        T &operator[](size_t i) { return data[i]; }
        const T &operator[](size_t i) const { return data[i]; }

        // 默认是列向量
        size_t rows() const { return is_row_vector ? 1 : N; }
        size_t cols() const { return is_row_vector ? N : 1; }

        // 从表达式赋值
        template <typename Expr>
        VectorN &operator=(const MatrixExpr<Expr> &expr)
        {
            for (size_t i = 0; i < N; ++i)
                data[i] = expr(i, 0);
            return *this;
        }

        // ------------------ 向量特有运算 ------------------

        // 点积
        T dot(const VectorN &other) const
        {
            T result = T::zero();
            for (size_t i = 0; i < N; ++i)
                result += data[i] * other.data[i];
            return result;
        }

        // 叉积 3D
        template <size_t M = N>
        typename std::enable_if<M == 3, VectorN>::type
        cross(const VectorN &other) const
        {
            return VectorN{
                data[1] * other[2] - data[2] * other[1],
                data[2] * other[0] - data[0] * other[2],
                data[0] * other[1] - data[1] * other[0]};
        }

        // L2范数
        T norm() const
        {
            return sqrt(dot(*this));
        }
        // 单位化
        VectorN normalize() const
        {
            T len = norm();
            if (len == T::zero())
                throw std::domain_error("Cannot normalize zero vector");

            // 显式创建结果向量，避免返回表达式模板
            VectorN result;
            T scale = T::identity() / len;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = data[i] * scale;
            }
            return result;
        }

        VectorN transpose() const
        {
            VectorN result = *this;
            result.is_row_vector = !is_row_vector;
            return result;
        }

        bool isRowVector() const { return is_row_vector; }

        friend std::ostream &operator<<(std::ostream &os, const VectorN &v)
        {
            const size_t rows = v.rows();
            const size_t cols = v.cols();
            const size_t total_elements = rows * cols;

            if (total_elements == 0)
            {
                return os << "[]";
            }

            if (total_elements == 1)
            {
                return os << "[[" << v(0, 0) << "]]";
            }

            if (v.isRowVector())
            {
                os << "[";
                for (size_t i = 0; i < cols; ++i)
                {
                    os << v(i, 0);
                    if (i + 1 < cols)
                    {
                        os << ", ";
                    }
                }
                return os << "]";
            }

            os << "[";
            for (size_t i = 0; i < rows; ++i)
            {
                if (cols == 1)
                {
                    os << "[" << v(i, 0) << "]";
                }
                else
                {
                    os << "[";
                    for (size_t j = 0; j < cols; ++j)
                    {
                        os << v(i, j);
                        if (j + 1 < cols)
                        {
                            os << ", ";
                        }
                    }
                    os << "]";
                }
                if (i + 1 < rows)
                {
                    os << ",\n ";
                }
            }
            return os << "]";
        }
    };

    using Vector2f = VectorN<Real, 2>;
    using Vector3f = VectorN<Real, 3>;
    using Vector4f = VectorN<Real, 4>;
    using Vector2c = VectorN<Complex, 2>;
    using Vector3c = VectorN<Complex, 3>;
}