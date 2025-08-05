#pragma once

namespace OxygenMath
{
    //前置声明避免循环依赖
    template <typename Derived>
    class MatrixBase;

    template <typename Derived>
    struct MatrixExpr : MatrixBase<Derived>
    {
        const Derived &derived() const { return *static_cast<const Derived *>(this); }
        Derived &derived() { return *static_cast<Derived *>(this); }

        using MatrixBase<Derived>::rows;
        using MatrixBase<Derived>::cols;
    };

    // 矩阵加法表达式
    template <typename Lhs, typename Rhs>
    struct MatrixAdd : MatrixExpr<MatrixAdd<Lhs, Rhs>>
    {
        const Lhs &lhs;
        const Rhs &rhs;

        MatrixAdd(const Lhs &l, const Rhs &r) : lhs(l), rhs(r)
        {
            if (!(l.rows() == r.rows() && l.cols() == r.cols()))
                throw std::invalid_argument("Matrix addition requires matrices of the same dimensions");
        }

        size_t rows() const { return lhs.rows(); }
        size_t cols() const { return lhs.cols(); }

        auto operator()(size_t i, size_t j) const -> decltype(lhs(i, j) + rhs(i, j))
        {
            return lhs(i, j) + rhs(i, j);
        }
    };

    // 矩阵减法表达式
    template <typename Lhs, typename Rhs>
    struct MatrixSub : MatrixExpr<MatrixSub<Lhs, Rhs>>
    {
        const Lhs &lhs;
        const Rhs &rhs;

        MatrixSub(const Lhs &l, const Rhs &r) : lhs(l), rhs(r)
        {
            if (!(l.rows() == r.rows() && l.cols() == r.cols()))
                throw std::invalid_argument("Matrix subtraction requires matrices of the same dimensions");
        }

        size_t rows() const { return lhs.rows(); }
        size_t cols() const { return lhs.cols(); }

        auto operator()(size_t i, size_t j) const -> decltype(lhs(i, j) - rhs(i, j))
        {
            return lhs(i, j) - rhs(i, j);
        }
    };

    // 矩阵乘法表达式
    template <typename Lhs, typename Rhs>
    struct MatrixMul : MatrixExpr<MatrixMul<Lhs, Rhs>>
    {
        const Lhs &lhs;
        const Rhs &rhs;

        MatrixMul(const Lhs &l, const Rhs &r) : lhs(l), rhs(r)
        {
            if (!(l.cols() == r.rows()))
                throw std::invalid_argument("In matrix multiplication, the number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        size_t rows() const { return lhs.rows(); }
        size_t cols() const { return rhs.cols(); }

        auto operator()(size_t i, size_t j) const -> decltype(lhs(i, 0) * rhs(0, j))
        {
            auto sum = lhs(i, 0) * rhs(0, j);
            for (size_t k = 1; k < lhs.cols(); ++k)
            {
                sum += lhs(i, k) * rhs(k, j);
            }
            return sum;
        }
    };

    // 数乘表达式（矩阵 * 标量）
    template <typename Mat, typename Scalar>
    struct MatrixScalarMul : MatrixExpr<MatrixScalarMul<Mat, Scalar>>
    {
        const Mat &mat;
        const Scalar scalar;

        MatrixScalarMul(const Mat &m, const Scalar &s) : mat(m), scalar(s) {}

        size_t rows() const { return mat.rows(); }
        size_t cols() const { return mat.cols(); }

        auto operator()(size_t i, size_t j) const -> decltype(mat(i, j) * scalar)
        {
            return mat(i, j) * scalar;
        }
    };

    // 数乘表达式（标量 * 矩阵）
    template <typename Scalar, typename Mat>
    struct ScalarMatrixMul : MatrixExpr<ScalarMatrixMul<Scalar, Mat>>
    {
        const Scalar scalar;
        const Mat &mat;

        ScalarMatrixMul(const Scalar &s, const Mat &m) : scalar(s), mat(m) {}

        size_t rows() const { return mat.rows(); }
        size_t cols() const { return mat.cols(); }

        auto operator()(size_t i, size_t j) const -> decltype(scalar * mat(i, j))
        {
            return scalar * mat(i, j);
        }
    };

    // 矩阵转置表达式
    template <typename Mat>
    struct MatrixTranspose : MatrixExpr<MatrixTranspose<Mat>>
    {
        const Mat &mat;

        MatrixTranspose(const Mat &m) : mat(m) {}

        size_t rows() const { return mat.cols(); }
        size_t cols() const { return mat.rows(); }

        auto operator()(size_t i, size_t j) const -> decltype(mat(j, i))
        {
            return mat(j, i);
        }
    };
    // 输出运算符
    template <typename Expr>
    std::ostream &operator<<(std::ostream &os, const MatrixExpr<Expr> &expr)
    {
        const Expr &e = static_cast<const Expr &>(expr);
        const size_t rows = e.rows();
        const size_t cols = e.cols();

        if (rows == 0 || cols == 0)
        {
            return os << "[]";
        }

        os << "[";
        for (size_t i = 0; i < rows; ++i)
        {
            if (i != 0)
                os << " ";

            os << "[";
            for (size_t j = 0; j < cols; ++j)
            {
                os << e(i, j);
                if (j + 1 < cols)
                {
                    os << ", ";
                }
            }
            os << "]";

            if (i + 1 < rows)
            {
                os << ",\n";
            }
        }
        return os << "]";
    }
}