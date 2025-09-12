#pragma once
#include <cstddef>
#include <type_traits>
#include "MatrixExpr.hpp"

namespace OxygenMath
{
    // 因为不支持自定义类型，所以我们需要一个类型特征来判断是否是标量类型
    template <typename T>
    struct is_scalar_type : std::is_arithmetic<T>
    {
    };
    //  所以为 Real 类型特化
    template <>
    struct is_scalar_type<Real> : std::true_type
    {
    };

    // 为 Complex 类型特化
    template <>
    struct is_scalar_type<Complex> : std::true_type
    {
    };

    /**
     * @brief 矩阵基类，使用CRTP实现静态多态
     *
     * 该类为所有矩阵类型提供统一的接口和基本运算操作。
     * 通过CRTP模式避免虚函数调用开销，同时实现代码复用。
     *
     * @tparam Derived 派生类类型，必须继承自MatrixBase
     */
    template <typename Derived>
    class MatrixBase
    {
    public:
        // CRTP：获取派生类引用
        const Derived &derived() const { return *static_cast<const Derived *>(this); }
        Derived &derived() { return *static_cast<Derived *>(this); }

        // 尺寸查询
        size_t rows() const { return derived().rows(); }
        size_t cols() const { return derived().cols(); }

        // ------------------ 运算符重载 ------------------

        // 矩阵乘法（A * B）
        template <typename Other>
        auto operator*(const MatrixBase<Other> &other) const
            -> MatrixMul<Derived, Other>
        {
            return MatrixMul<Derived, Other>(derived(), other.derived());
        }

        // 数乘：矩阵 * 标量
        template <typename S>
        auto operator*(const S &scalar) const
            -> typename std::enable_if<is_scalar_type<S>::value,
                                       MatrixScalarMul<Derived, S>>::type
        {
            return MatrixScalarMul<Derived, S>(derived(), scalar);
        }

        // 加法
        template <typename Other>
        auto operator+(const MatrixBase<Other> &other) const
            -> MatrixAdd<Derived, Other>
        {
            return MatrixAdd<Derived, Other>(derived(), other.derived());
        }

        // 减法
        template <typename Other>
        auto operator-(const MatrixBase<Other> &other) const
            -> MatrixSub<Derived, Other>
        {
            return MatrixSub<Derived, Other>(derived(), other.derived());
        }

        // 转置
        auto transpose() const -> MatrixTranspose<Derived>
        {
            return MatrixTranspose<Derived>(derived());
        }
    };

    // 全局运算符：标量 * 矩阵
    template <typename S, typename Derived>
    auto operator*(const S &scalar, const MatrixBase<Derived> &mat)
        -> typename std::enable_if<is_scalar_type<S>::value,
                                   ScalarMatrixMul<S, Derived>>::type
    {
        return ScalarMatrixMul<S, Derived>(scalar, mat.derived());
    }
}