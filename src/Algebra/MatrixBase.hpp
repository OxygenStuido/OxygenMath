// MatrixBase.hpp
#pragma once
#include <cstddef>
#include <type_traits>
#include "MatrixExpr.hpp"

namespace OxygenMath
{
    template <typename T>
    struct is_scalar_type : std::is_arithmetic<T>
    {
    };

    // 为 Real 类型特化
    template <>
    struct is_scalar_type<Real> : std::true_type
    {
    };

    // 为 Complex 类型特化
    template <>
    struct is_scalar_type<Complex> : std::true_type
    {
    };

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
            -> decltype(MatrixMul<Derived, Other>(derived(), other.derived()))
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
            -> decltype(MatrixAdd<Derived, Other>(derived(), other.derived()))
        {
            return MatrixAdd<Derived, Other>(derived(), other.derived());
        }

        // 减法
        template <typename Other>
        auto operator-(const MatrixBase<Other> &other) const
            -> decltype(MatrixSub<Derived, Other>(derived(), other.derived()))
        {
            return MatrixSub<Derived, Other>(derived(), other.derived());
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