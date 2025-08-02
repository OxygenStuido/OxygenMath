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

    public:
        // 默认构造函数（零向量）
        VectorN() : data{}
        {
            for (size_t i = 0; i < N; ++i)
                data[i] = T::zero();
        }

        // 初始化列表构造函数
        VectorN(std::initializer_list<T> init)
        {
            if (init.size() != N)
                throw std::invalid_argument("Initializer list size does not match vector dimension");

            std::copy(init.begin(), init.end(), data.begin());
        }

        // 访问元素 (矩阵接口)
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

        // 向量风格访问
        T &operator[](size_t i) { return data[i]; }
        const T &operator[](size_t i) const { return data[i]; }

        // 维度信息
        size_t rows() const { return N; }
        size_t cols() const { return 1; }

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

        // 叉积 (仅限3D向量)
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

            return (*this) * (T::identity() / len);
        }

        friend std::ostream &operator<<(std::ostream &os, const VectorN &v)
        {
            os << "[";
            for (size_t i = 0; i < N; ++i)
            {
                os << v.data[i];
                if (i < N - 1)
                    os << ", ";
            }
            os << "]^T";
            return os;
        }
    };

    using Vector2f = VectorN<Real, 2>;
    using Vector3f = VectorN<Real, 3>;
    using Vector4f = VectorN<Real, 4>;
    using Vector2c = VectorN<Complex, 2>;
    using Vector3c = VectorN<Complex, 3>;
}