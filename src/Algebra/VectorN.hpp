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

    template <typename T>
    class Vec2 : public VectorN<T, 2>
    {
    public:
        // 继承基类构造函数
        using VectorN<T, 2>::VectorN;

        T getX() const { return (*this)[0]; }
        T getY() const { return (*this)[1]; }
        // 叉积
        T cross(const Vec2 &v) const
        {
            static_assert(std::is_same<T, Real>::value,
                          "Cross product requires Real type");
            return (*this)[0] * v[1] - (*this)[1] * v[0];
        }

        // 长度计算
        T length() const { return this->l2_norm(); }
        T lengthSquare() const { return this->l2_normSquare(); }

        Vec2 normalized() const { return this->l2_normalization(); }
    };

    template <typename T>
    class Vec3 : public VectorN<T, 3>
    {
    public:
        // 继承基类构造函数
        using VectorN<T, 3>::VectorN;
        // 叉积
        T cross(const Vec3 &v) const
        {
            static_assert(std::is_same<T, Real>::value,
                          "Cross product requires Real type");
            return Vec3((*this)[1] * v[2] - (*this)[2] * v[1],
                        (*this)[2] * v[0] - (*this)[0] * v[2],
                        (*this)[0] * v[1] - (*this)[1] * v[0]);
        }

        T getX() const { return (*this)[0]; }
        T getY() const { return (*this)[1]; }
        T getZ() const { return (*this)[2]; }

        T length() const { return this->l2_norm(); }
        T lengthSquare() const { return this->l2_normSquare(); }

        Vec3 normalized() const { return this->l2_normalization(); }
    };

    template <typename T>
    class Vec4 : public VectorN<T, 4>
    {
    public:
        // 继承基类构造函数
        using VectorN<T, 4>::VectorN;

        // 叉积
        T cross(const Vec4 &v) const
        {
            static_assert(std::is_same<T, Real>::value,
                          "Cross product requires Real type");
            return Vec4((*this)[1] * v[2] - (*this)[2] * v[1],
                        (*this)[2] * v[0] - (*this)[0] * v[2],
                        (*this)[0] * v[1] - (*this)[1] * v[0],
                        T::zero()); // 4D向量的叉积结果在第四维为零
        }
        T getX() const { return (*this)[0]; }
        T getY() const { return (*this)[1]; }
        T getZ() const { return (*this)[2]; }
        T getW() const { return (*this)[3]; }

        T length() const { return this->l2_norm(); }
        T lengthSquare() const { return this->l2_normSquare(); }

        Vec4 normalized() const { return this->l2_normalization(); }
    };

    template <>
    class Vec2<Real> : public VectorN<Real, 2>
    {
    public:
        // 构造函数优化
        Vec2() : VectorN<Real, 2>({Real::zero(), Real::zero()}) {}
        Vec2(Real x, Real y) : VectorN<Real, 2>({x, y}) {}

        // 高性能叉积
        Real cross(const Vec2 &v) const
        {
            return (*this)[0] * v[1] - (*this)[1] * v[0];
        }

        Real length() const
        {
            return sqrt((*this)[0] * (*this)[0] + (*this)[1] * (*this)[1]);
        }

        Vec2 rotate(Real angle) const
        {
            Real cost = cos(angle), sint = sin(angle);
            return {
                (*this)[0] * cost - (*this)[1] * sint,
                (*this)[0] * sint + (*this)[1] * cost};
        }
        Real getX() const { return (*this)[0]; }
        Real getY() const { return (*this)[1]; }
    };

    template <>
    class Vec3<Real> : public VectorN<Real, 3>
    {
    public:
        // 构造函数
        Vec3() : VectorN<Real, 3>({Real::zero(), Real::zero(), Real::zero()}) {}
        Vec3(Real x, Real y, Real z) : VectorN<Real, 3>({x, y, z}) {}

        // 叉积
        Vec3 cross(const Vec3 &v) const
        {
            return Vec3((*this)[1] * v[2] - (*this)[2] * v[1],
                        (*this)[2] * v[0] - (*this)[0] * v[2],
                        (*this)[0] * v[1] - (*this)[1] * v[0]);
        }

        Real length() const
        {
            return sqrt((*this)[0] * (*this)[0] + (*this)[1] * (*this)[1] + (*this)[2] * (*this)[2]);
        }
        Real getX() const { return (*this)[0]; }
        Real getY() const { return (*this)[1]; }
        Real getZ() const { return (*this)[2]; }

    };

    template <>
    class Vec4<Real> : public VectorN<Real, 4>
    {
    public:
        // 构造函数
        Vec4() : VectorN<Real, 4>({Real::zero(), Real::zero(), Real::zero(), Real::zero()}) {}
        Vec4(Real x, Real y, Real z, Real w) : VectorN<Real, 4>({x, y, z, w}) {}

        // 叉积
        Vec4 cross(const Vec4 &v) const
        {
            return Vec4((*this)[1] * v[2] - (*this)[2] * v[1],
                        (*this)[2] * v[0] - (*this)[0] * v[2],
                        (*this)[0] * v[1] - (*this)[1] * v[0],
                        Real::zero()); // 4D向量的叉积结果在第四维为零
        }

        Real length() const
        {
            return sqrt((*this)[0] * (*this)[0] + (*this)[1] * (*this)[1] + (*this)[2] * (*this)[2]);
        }
        Real getX() const { return (*this)[0]; }
        Real getY() const { return (*this)[1]; }
        Real getZ() const { return (*this)[2]; }
        Real getW() const { return (*this)[3]; }
    };

}