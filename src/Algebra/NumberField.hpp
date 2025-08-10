/**
 * @file NumberField.hpp
 * @brief 这是一个数域的抽象基类，定义了数域的基本操作和接口。
 * @details 数域需要支持加法、减法、乘法和除法操作以及零元(zero)和单位元(identity)的定义。
 * @tparam T 数域的具体类型，必须继承自 NumberField<T>。
 * @note 该类使用 CRTP 设计模式，以便在派生类中实现具体的数域操作。
 */
#pragma once
#include <iostream>
#include <cmath>

namespace OxygenMath
{
    // CRTP设计模式
    template <typename T>
    class NumberField
    {
    public:

        // // 数域需保持加法 减法 乘法 除法
        // T add(const T &other) const { return static_cast<const T *>(this)->add(other); }
        // T sub(const T &other) const { return static_cast<const T *>(this)->sub(other); }
        // T mul(const T &other) const { return static_cast<const T *>(this)->mul(other); }
        // T div(const T &other) const { return static_cast<const T *>(this)->div(other); }

        // 数域一定包含零元
        static T zero() { return T::zero(); }
        // 数域一定包含单位元
        static T identity() { return T::identity(); }

        // 操作符重载
        friend T operator+(const T &lhs, const T &rhs) { return lhs.add(rhs); }
        friend T operator-(const T &lhs, const T &rhs) { return lhs.sub(rhs); }
        friend T operator*(const T &lhs, const T &rhs) { return lhs.mul(rhs); }
        friend T operator/(const T &lhs, const T &rhs) { return lhs.div(rhs); }
    };

    class Real : public NumberField<Real>
    {
    public:
        double data;

        Real(double d = 0.0) : data(d) {}

        // Real + Real
        Real add(const Real &other) const { return Real(data + other.data); }
        // Real - Real
        Real sub(const Real &other) const { return Real(data - other.data); }
        // Real * Real
        Real mul(const Real &other) const { return Real(data * other.data); }
        // Real / Real
        Real div(const Real &other) const
        {
            if (other.data == 0.0)
                throw std::invalid_argument("Division by zero");
            return Real(data / other.data);
        }
        // 复合赋值运算符
        Real &operator+=(const Real &other)
        {
            data += other.data;
            return *this;
        }
        Real &operator-=(const Real &other)
        {
            data -= other.data;
            return *this;
        }
        Real &operator*=(const Real &other)
        {
            data *= other.data;
            return *this;
        }
        Real &operator/=(const Real &other)
        {
            if (other.data == 0.0)
                throw std::invalid_argument("Division by zero");
            data /= other.data;
            return *this;
        }
        // 逻辑运算符重载
        bool operator>=(const Real &rhs) const { return data >= rhs.data; }
        bool operator>(const Real &rhs) const { return data > rhs.data; }
        bool operator<=(const Real &rhs) const { return data <= rhs.data; }
        bool operator<(const Real &rhs) const { return data < rhs.data; }
        bool operator==(const Real &rhs) const { return data == rhs.data; }
        bool operator!=(const Real &rhs) const { return data != rhs.data; }
        friend Real operator-(const Real &real) { return Real(-real.data); }

        // 支持 sqrt() 函数以提供L2范数
        Real sqrt() const
        {
            if (data < 0.0)
                throw std::domain_error("Square root of negative number");
            return Real(std::sqrt(data));
        }

        static Real zero() { return Real(0.0); }
        static Real identity() { return Real(1.0); }

        friend std::ostream &operator<<(std::ostream &os, const Real &r)
        {
            os << r.data;
            return os;
        }
    };

    class Complex : public NumberField<Complex>
    {
    public:
        double real, imag;

        Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

        // Complex + Complex
        Complex add(const Complex &other) const
        {
            return Complex(real + other.real, imag + other.imag);
        }

        // Complex - Complex
        Complex sub(const Complex &other) const
        {
            return Complex(real - other.real, imag - other.imag);
        }

        // Complex * Complex
        Complex mul(const Complex &other) const
        {
            double r = real * other.real - imag * other.imag;
            double i = real * other.imag + imag * other.real;
            return Complex(r, i);
        }

        // Complex / Complex
        Complex div(const Complex &other) const
        {
            double denom = other.real * other.real + other.imag * other.imag;
            if (denom == 0.0)
                throw std::invalid_argument("Division by zero");

            double r = (real * other.real + imag * other.imag) / denom;
            double i = (imag * other.real - real * other.imag) / denom;
            return Complex(r, i);
        }
        // 复合赋值运算符
        Complex &operator+=(const Complex &other)
        {
            real += other.real;
            imag += other.imag;
            return *this;
        }

        Complex &operator-=(const Complex &other)
        {
            real -= other.real;
            imag -= other.imag;
            return *this;
        }

        Complex &operator*=(const Complex &other)
        {
            double r = real * other.real - imag * other.imag;
            double i = real * other.imag + imag * other.real;
            real = r;
            imag = i;
            return *this;
        }

        Complex &operator/=(const Complex &other)
        {
            double denom = other.real * other.real + other.imag * other.imag;
            if (denom == 0.0)
                throw std::invalid_argument("Division by zero");

            double r = (real * other.real + imag * other.imag) / denom;
            double i = (imag * other.real - real * other.imag) / denom;
            real = r;
            imag = i;
            return *this;
        }
        Complex sqrt() const
        {
            double r = std::sqrt(std::sqrt(real * real + imag * imag));
            double theta = std::atan2(imag, real) / 2.0;
            return Complex(r * std::cos(theta), r * std::sin(theta));
        }

        static Complex zero() { return Complex(0.0, 0.0); }
        static Complex identity() { return Complex(1.0, 0.0); }

        friend std::ostream &operator<<(std::ostream &os, const Complex &c)
        {
            os << c.real << (c.imag >= 0 ? "+" : "") << c.imag << "i";
            return os;
        }
    };
}