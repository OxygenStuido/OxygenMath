#pragma once
#include <vector>
#include <cmath>
#include "AlgebraTool.hpp"
#include "NumberField.hpp"
namespace OxygenMath
{

    template <typename T>
    class Vector
    {
        static_assert(std::is_base_of<NumberField<T>, T>::value,
                      "Vector<T> requires T to inherit from NumberField<T>");

    private:
        std::vector<T> data;
        bool is_row = true;

    public:
        size_t size() const { return data.size(); }

        Vector(size_t n = 0) : data(n) {}
        Vector(const std::initializer_list<T> &list) : data(list) {}

        const T &operator[](size_t i) const
        {
            return data[i];
        }

        T &operator[](size_t i)
        {
            return data[i];
        }

        // 向量加法：Vector + Vector
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
        Vector<T> operator*(const T &scalar) const
        {
            Vector<T> result(size());
            for (size_t i = 0; i < size(); ++i)
                result[i] = data[i] * scalar;
            return result;
        }

        // 向量标量乘法：Scalar * Vector
        friend Vector<T> operator*(const T &scalar, const Vector<T> &vec)
        {
            Vector<T> result(vec.size());
            for (size_t i = 0; i < vec.size(); ++i)
                result[i] = vec.data[i] * scalar;
            return result;
        }

        // 向量点积：Vector * Vector
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
        void transpose()
        {
            is_row = !is_row;
        }

        // L2 范数：sqrt(sum(x_i^2))
        T l2_norm() const
        {
            T sum = T::zero();
            for (const auto &val : data)
            {
                sum = sum + val * val;
            }
            return sqrt(sum);
        }

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
            {
                os << "^T";
            }
            return os;
        }
    };
}