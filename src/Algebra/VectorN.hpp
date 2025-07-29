#pragma once
#include <array>
#include <cmath>
#include "NumberField.hpp"
#include "../Constants.hpp"
#include "AlgebraTool.hpp"
namespace OxygenMath
{
    /*! \brief 静态向量模板类，支持固定长度的线性代数运算
     * \tparam T 向量元素类型，必须继承自NumberField
     * \tparam N 向量维度
     * \tparam IsRow 是否为行向量(默认为true)
     */
    template <typename T, size_t N, bool IsRow = true>
    class VectorN : public std::array<T, N>
    {
        static_assert(std::is_base_of<NumberField<T>, T>::value,
                      "VectorN<T, N> requires T to inherit from NumberField<T>");

    public:
        using Base = std::array<T, N>;
        using Base::Base;

        /*! \brief 默认构造函数，元素初始化为零 */
        VectorN() : Base()
        {
            for (auto &elem : *this)
            {
                elem = T::zero();
            }
        }

        /*! \brief 使用初始化列表构造向量 */
        VectorN(const std::initializer_list<T> &list)
        {
            size_t i = 0;
            for (const auto &val : list)
            {
                if (i >= N)
                    break;
                (*this)[i++] = val;
            }
        }

        /*! \brief 向量加法 */
        VectorN<T, N, IsRow> operator+(const VectorN<T, N, IsRow> &other) const
        {
            VectorN<T, N, IsRow> result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = (*this)[i] + other[i];
            }
            return result;
        }

        /*! \brief 向量减法 */
        VectorN<T, N, IsRow> operator-(const VectorN<T, N, IsRow> &other) const
        {
            VectorN<T, N, IsRow> result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = (*this)[i] - other[i];
            }
            return result;
        }

        /*! \brief 向量标量乘法 */
        VectorN<T, N, IsRow> operator*(const T &scalar) const
        {
            VectorN<T, N, IsRow> result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = (*this)[i] * scalar;
            }
            return result;
        }

        /*! \brief 标量乘以向量 */
        friend VectorN<T, N, IsRow> operator*(const T &scalar, const VectorN<T, N, IsRow> &vec)
        {
            return vec * scalar;
        }

        /*! \brief 获得相反向量 */
        VectorN<T, N, IsRow> operator-() const
        {
            VectorN<T, N, IsRow> result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = -(*this)[i];
            }
            return result;
        }

        /*! \brief 向量点积 */
        T dot(const VectorN<T, N, IsRow> &other) const
        {
            T result = T::zero();
            for (size_t i = 0; i < N; ++i)
            {
                result += (*this)[i] * other[i];
            }
            return result;
        }

        /*! \brief 向量转置 */
        VectorN<T, N, !IsRow> transpose() const
        {
            VectorN<T, N, !IsRow> result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = (*this)[i];
            }
            return result;
        }

        /*! \brief 输出向量到流 */
        friend std::ostream &operator<<(std::ostream &os, const VectorN<T, N, IsRow> &vec)
        {
            os << "[ ";
            for (size_t i = 0; i < N; ++i)
            {
                os << vec[i];
                if (i != N - 1)
                    os << ", ";
            }
            os << " ]";
            if (!IsRow)
                os << "^T";
            return os;
        }

        /*! \brief 检查正交性 */
        static bool checkOrthogonality(const VectorN &v1, const VectorN &v2)
        {
            if (abs(v1.dot(v2)) < Constants::epsilon)
                return true;
            return false;
        }
    };

    /*! \brief 实数静态向量特化类 */
    template <size_t N, bool IsRow>
    class VectorN<Real, N, IsRow> : public std::array<Real, N>
    {
    public:
        using Base = std::array<Real, N>;
        using Base::Base;

        /*! \brief 默认构造函数，元素初始化为零 */
        VectorN() : Base()
        {
            for (auto &elem : *this)
            {
                elem = Real::zero();
            }
        }

        /*! \brief 使用初始化列表构造向量 */
        VectorN(const std::initializer_list<Real> &list)
        {
            size_t i = 0;
            for (const auto &val : list)
            {
                if (i >= N)
                    break;
                (*this)[i++] = val;
            }
        }

        /*! \brief 向量加法 */
        VectorN<Real, N, IsRow> operator+(const VectorN<Real, N, IsRow> &other) const
        {
            VectorN<Real, N, IsRow> result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = (*this)[i] + other[i];
            }
            return result;
        }

        /*! \brief 向量减法 */
        VectorN<Real, N, IsRow> operator-(const VectorN<Real, N, IsRow> &other) const
        {
            VectorN<Real, N, IsRow> result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = (*this)[i] - other[i];
            }
            return result;
        }

        /*! \brief 向量标量乘法 */
        VectorN<Real, N, IsRow> operator*(const Real &scalar) const
        {
            VectorN<Real, N, IsRow> result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = (*this)[i] * scalar;
            }
            return result;
        }

        /*! \brief 标量乘以向量 */
        friend VectorN<Real, N, IsRow> operator*(const Real &scalar, const VectorN<Real, N, IsRow> &vec)
        {
            return vec * scalar;
        }

        /*! \brief 获得相反向量 */
        VectorN<Real, N, IsRow> operator-() const
        {
            VectorN<Real, N, IsRow> result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = -(*this)[i];
            }
            return result;
        }

        /*! \brief 向量归一化 */
        VectorN<Real, N, IsRow> l2_normalization() const
        {
            VectorN<Real, N, IsRow> result;
            Real norm = this->l2_norm();
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = (*this)[i] / norm;
            }
            return result;
        }

        /*! \brief 向量点积 */
        Real dot(const VectorN<Real, N, IsRow> &other) const
        {
            Real result = Real::zero();
            for (size_t i = 0; i < N; ++i)
            {
                result += (*this)[i] * other[i];
            }
            return result;
        }

        /*! \brief 向量转置 */
        VectorN<Real, N, !IsRow> transpose() const
        {
            VectorN<Real, N, !IsRow> result;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = (*this)[i];
            }
            return result;
        }

        /*! \brief 计算向量L2范数 */
        Real l2_norm() const
        {
            Real sum = Real::zero();
            for (const auto &val : *this)
            {
                sum += val * val;
            }
            return sqrt(sum);
        }

        /*! \brief 计算向量L2范数的平方 */
        Real l2_normSquare() const
        {
            Real sum = Real::zero();
            for (const auto &val : *this)
            {
                sum += val * val;
            }
            return sum;
        }

        /*! \brief 输出向量到流 */
        friend std::ostream &operator<<(std::ostream &os, const VectorN<Real, N, IsRow> &vec)
        {
            os << "[ ";
            for (size_t i = 0; i < N; ++i)
            {
                os << vec[i];
                if (i != N - 1)
                    os << ", ";
            }
            os << " ]";
            if (!IsRow)
                os << "^T";
            return os;
        }

        /*! \brief 检查正交性 */
        static bool checkOrthogonality(const VectorN &v1, const VectorN &v2)
        {
            if (v1.dot(v2) < Constants::epsilon)
                return true;
            return false;
        }
    };
}