#pragma once
#include <vector>
#include <cmath>
#include "NumberField.hpp"
namespace OxygenMath
{
    // template <typename T>
    // class Vector
    // {
    // public:
    //     Vector() : size(0) {}
    //     Vector(size_t size) : size(size), data(size, T()) {}

    //     // Access element at index i
    //     T &operator[](size_t i)
    //     {
    //         if (i >= size)
    //         {
    //             throw std::out_of_range("Index out of range");
    //         }
    //         return data[i];
    //     }

    //     const T &operator[](size_t i) const
    //     {
    //         if (i >= size)
    //         {
    //             throw std::out_of_range("Index out of range");
    //         }
    //         return data[i];
    //     }

    //     // Get the size of the vector
    //     size_t getSize() const
    //     {
    //         return size;
    //     }

    //     // Vector addition
    //     Vector<T> operator+(const Vector<T> &other) const
    //     {
    //         if (size != other.size)
    //         {
    //             throw std::invalid_argument("Vectors must be of the same size");
    //         }
    //         Vector<T> result(size);
    //         for (size_t i = 0; i < size; ++i)
    //         {
    //             result[i] = data[i] + other.data[i];
    //         }
    //         return result;
    //     }

    //     // Vector subtraction
    //     Vector<T> operator-(const Vector<T> &other) const
    //     {
    //         if (size != other.size)
    //         {
    //             throw std::invalid_argument("Vectors must be of the same size");
    //         }
    //         Vector<T> result(size);
    //         for (size_t i = 0; i < size; ++i)
    //         {
    //             result[i] = data[i] - other.data[i];
    //         }
    //         return result;
    //     }

    //     // Scalar multiplication
    //     friend Vector<T> operator*(const T &scalar, const Vector<T> &vec)
    //     {
    //         Vector<T> result(vec.size);
    //         for (size_t i = 0; i < vec.size; ++i)
    //         {
    //             result[i] = vec.data[i] * scalar;
    //         }
    //         return result;
    //     }

    //     Vector<T> operator*(const T &scalar)
    //     {
    //         Vector<T> result(size);
    //         for (size_t i = 0; i < size; ++i)
    //         {
    //             result[i] = data[i] * scalar;
    //         }
    //         return result;
    //     }

    //     // Friend function to allow output streaming
    //     friend std::ostream &operator<<(std::ostream &os, const Vector<T> &v)
    //     {
    //         os << "[";
    //         for (size_t i = 0; i < v.size; ++i)
    //         {
    //             os << v.data[i];
    //             if (i != v.size - 1)
    //             {
    //                 os << ", ";
    //             }
    //         }
    //         os << "]";
    //         if (!v.is_row)
    //         {
    //             std::cout << "^T";
    //         }
    //         return os;
    //     }

    //     void Transpose()
    //     {
    //         is_row = !is_row;
    //     }

    //     real EuclideanNorm()
    //     {
    //         double sum = 0;
    //         for (const auto &value : data)
    //         {
    //             sum += (value * value).norm();
    //         }
    //         return std::pow(sum,0.5);
    //     }

    //     real ManhattanNorm()
    //     {
    //         real sum = 0;
    //         for (const auto &value : data)
    //         {
    //             sum += value.norm();
    //         }
    //         return sum;
    //     }

    // private:
    //     bool is_row = true; // It indicates whether the vector is a row vector; if not, it is a column vector
    //     size_t size;
    //     std::vector<T> data;
    // };
}