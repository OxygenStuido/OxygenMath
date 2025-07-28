#pragma once
#include <vector>
#include <cmath>
#include "AlgebraTool.hpp"
#include "NumberField.hpp"
#include "../Constants.hpp"
namespace OxygenMath
{
    /*! \brief 向量模板类，支持基本线性代数运算
     * \tparam T 向量元素类型，必须继承自NumberField
     */
    template <typename T>
    class Vector
    {
        static_assert(std::is_base_of<NumberField<T>, T>::value,
                      "Vector<T> requires T to inherit from NumberField<T>");

    private:
        std::vector<T> data;
        bool is_row = true;

    public:
        /*! \brief 获取向量大小
         * \return 向量元素数量
         */
        size_t size() const { return data.size(); }

        /*! \brief 构造指定大小的向量
         * \param n 向量大小
         */
        /*! \brief 构造指定大小的实数向量
         * \param n 向量大小
         */
        Vector(size_t n = 0) : data(n) {}
        /*! \brief 使用初始化列表构造向量
         * \param list 初始化列表
         */
        Vector(const std::initializer_list<T> &list) : data(list) {}

        /*! \brief 常量下标访问运算符
         * \param i 索引
         * \return 常量引用
         */
        const T &operator[](size_t i) const
        {
            return data[i];
        }

        T &operator[](size_t i)
        {
            return data[i];
        }

        // 向量加法：Vector + Vector
        /*! \brief 向量加法
         * \param other 另一个向量
         * \return 相加结果
         * \exception std::invalid_argument 向量大小不匹配时抛出
         */
        Vector<T> operator+(const Vector<T> &other) const
        {
            if (size() != other.size())
                throw std::invalid_argument("Vector size mismatch in addition");

            Vector<T> result(size());
            for (size_t i = 0; i < size(); ++i)
                result[i] = data[i] + other.data[i]; // 使用 operator+
            return result;
        }

        // 向量减法：Vector - Vector
        /*! \brief 向量减法
         * \param other 另一个向量
         * \return 相减结果
         * \exception std::invalid_argument 向量大小不匹配时抛出
         */
        Vector<T> operator-(const Vector<T> &other) const
        {
            if (size() != other.size())
                throw std::invalid_argument("Vector size mismatch in subtraction");

            Vector<T> result(size());
            for (size_t i = 0; i < size(); ++i)
                result[i] = data[i] - other.data[i];
            return result;
        }

        // 向量标量乘法：Vector * Scalar
        /*! \brief 向量标量乘法
         * \param scalar 标量值
         * \return 相乘结果
         */
        Vector<T> operator*(const T &scalar) const
        {
            Vector<T> result(size());
            for (size_t i = 0; i < size(); ++i)
                result[i] = data[i] * scalar;
            return result;
        }

        // 向量标量乘法：Scalar * Vector
        /*! \brief 标量乘以向量
         * \param scalar 标量值
         * \param vec 向量
         * \return 相乘结果
         */
        friend Vector<T> operator*(const T &scalar, const Vector<T> &vec)
        {
            Vector<T> result(vec.size());
            for (size_t i = 0; i < vec.size(); ++i)
                result[i] = vec.data[i] * scalar;
            return result;
        }

        /*! \brief 获得相反向量
         * \return 相反向量
         */
        Vector<T> operator-() const
        {
            Vector<T> result(size());
            for (size_t i = 0; i < size(); ++i)
                result[i] = -data[i];
            return result;
        }

        // 向量点积：Vector * Vector
        /*! \brief 向量点积
         * \param other 另一个向量
         * \return 点积结果
         * \exception std::invalid_argument 向量大小不匹配时抛出
         */
        T dot(const Vector<T> &other) const
        {
            if (size() != other.size())
                throw std::invalid_argument("Vector size mismatch in dot product");

            T result = T::zero();
            for (size_t i = 0; i < size(); ++i)
                result = result + data[i] * other.data[i];
            return result;
        }

        // 向量转置
        /*! \brief 向量转置（行向量转列向量或列向量转行向量） */
        void transpose()
        {
            is_row = !is_row;
        }

        // L2 范数：sqrt(sum(x_i^2))
        /*! \brief 计算向量L2范数（欧几里得范数）
         * \return 范数结果
         */
        T l2_norm() const
        {
            T sum = T::zero();
            for (const auto &val : data)
                sum = sum + val * val;
            return sqrt(sum);
        }

        /*! \brief 输出向量到流
         * \param os 输出流
         * \param vec 向量
         * \return 输出流引用
         */
        friend std::ostream &operator<<(std::ostream &os, const Vector<T> &vec)
        {
            os << "[ ";
            for (size_t i = 0; i < vec.size(); ++i)
            {
                os << vec.data[i];
                if (i != vec.size() - 1)
                    os << ", ";
            }
            os << " ]";
            if (!vec.is_row)
                os << "^T";
            return os;
        }

        static bool checkOrthogonality(const Vector &v1, const Vector &v2)
        {
            if (v1.dot(v2) < Constants::epsilon)
                return true;
            return false;
        }
    };

    /*! \brief 实数向量特化类
     */
    template <>
    class Vector<Real>
    {
    private:
        std::vector<Real> data;
        bool is_row = true;

    public:
        size_t size() const { return data.size(); }

        Vector(size_t n = 0) : data(n) {}
        /*! \brief 使用初始化列表构造实数向量
         * \param list 初始化列表
         */
        Vector(const std::initializer_list<Real> &list) : data(list) {}

        /*! \brief 常量下标访问运算符
         * \param i 索引
         * \return 常量引用
         */
        const Real &operator[](size_t i) const
        {
            return data[i];
        }

        Real &operator[](size_t i)
        {
            return data[i];
        }

        // 向量加法：Vector + Vector
        /*! \brief 向量加法
         * \param other 另一个向量
         * \return 相加结果
         * \exception std::invalid_argument 向量大小不匹配时抛出
         */
        Vector<Real> operator+(const Vector<Real> &other) const
        {
            if (size() != other.size())
                throw std::invalid_argument("Vector size mismatch in addition");

            Vector<Real> result(size());
            for (size_t i = 0; i < size(); ++i)
                result[i] = data[i] + other.data[i]; // 使用 operator+
            return result;
        }

        // 向量减法：Vector - Vector
        /*! \brief 向量减法
         * \param other 另一个向量
         * \return 相减结果
         * \exception std::invalid_argument 向量大小不匹配时抛出
         */
        Vector<Real> operator-(const Vector<Real> &other) const
        {
            if (size() != other.size())
                throw std::invalid_argument("Vector size mismatch in subtraction");

            Vector<Real> result(size());
            for (size_t i = 0; i < size(); ++i)
                result[i] = data[i] - other.data[i];
            return result;
        }

        // 向量标量乘法：Vector * Scalar
        /*! \brief 向量标量乘法
         * \param scalar 标量值
         * \return 相乘结果
         */
        Vector<Real> operator*(const Real &scalar) const
        {
            Vector<Real> result(size());
            for (size_t i = 0; i < size(); ++i)
                result[i] = data[i] * scalar;
            return result;
        }

        // 向量标量乘法：Scalar * Vector
        /*! \brief 标量乘以向量
         * \param scalar 标量值
         * \param vec 向量
         * \return 相乘结果
         */
        friend Vector<Real> operator*(const Real &scalar, const Vector<Real> &vec)
        {
            Vector<Real> result(vec.size());
            for (size_t i = 0; i < vec.size(); ++i)
                result[i] = vec.data[i] * scalar;
            return result;
        }

        /*! \brief 获得相反向量
         * \return 相反向量
         */
        Vector<Real> operator-() const
        {
            Vector<Real> result(size());
            for (size_t i = 0; i < size(); ++i)
                result[i] = -data[i];
            return result;
        }

        /*! \brief 向量归一化
         * \return 归一化后的向量(单位向量)
         */
        Vector<Real> l2_normalization() const
        {
            Vector<Real> result(size());
            Real norm = this->l2_norm();
            for (size_t i = 0; i < size(); ++i)
                result[i] = data[i] / norm;
            return result;
        }

        // 向量点积：Vector * Vector
        /*! \brief 向量点积
         * \param other 另一个向量
         * \return 点积结果
         * \exception std::invalid_argument 向量大小不匹配时抛出
         */
        Real dot(const Vector<Real> &other) const
        {
            if (size() != other.size())
                throw std::invalid_argument("Vector size mismatch in dot product");

            Real result = Real::zero();
            for (size_t i = 0; i < size(); ++i)
                result = result + data[i] * other.data[i];
            return result;
        }

        // 向量转置
        void transpose()
        {
            is_row = !is_row;
        }

        // L2 范数：sqrt(sum(x_i^2))
        /*! \brief 计算向量L2范数（欧几里得范数）
         * \return 范数结果
         */
        Real l2_norm() const
        {
            Real sum = Real::zero();
            for (const auto &val : data)
                sum = sum + val * val;
            return sqrt(sum);
        }

        /*! \brief 计算向量L2范数的平方更快的速度（欧几里得范数）
         * \return 范数结果
         */
        Real l2_normSquare() const
        {
            Real sum = Real::zero();
            for (const auto &val : data)
                sum = sum + val * val;
            return sum;
        }

        /*! \brief 输出实数向量到流
         * \param os 输出流
         * \param vec 实数向量
         * \return 输出流引用
         */
        friend std::ostream &operator<<(std::ostream &os, const Vector<Real> &vec)
        {
            os << "[ ";
            for (size_t i = 0; i < vec.size(); ++i)
            {
                os << vec.data[i];
                if (i != vec.size() - 1)
                    os << ", ";
            }
            os << " ]";
            if (!vec.is_row)
                os << "^T";
            return os;
        }

        static bool checkOrthogonality(const Vector &v1, const Vector &v2)
        {
            if (v1.dot(v2) < Constants::epsilon)
                return true;
            return false;
        }
    };

}