#pragma once
#include <iostream>
// CRTP设计模式
namespace OxygenMath
{
    template <typename T>
    class NumberField
    {
    public:
        virtual ~NumberField() = default;

        T add(const T &other) const
        {
            return static_cast<const T *>(this)->add(other);
        }

        T sub(const T &other) const
        {
            return static_cast<const T *>(this)->sub(other);
        }

        T mul(const T &other) const
        {
            return static_cast<const T *>(this)->mul(other);
        }

        T div(const T &other) const
        {
            return static_cast<const T *>(this)->div(other);
        }

        static T zero() { return T::zero(); }
        static T identity() { return T::identity(); }

        friend T operator+(const T &lhs, const T &rhs)
        {
            return lhs.add(rhs);
        }

        friend T operator-(const T &lhs, const T &rhs)
        {
            return lhs.sub(rhs);
        }

        friend T operator*(const T &lhs, const T &rhs)
        {
            return lhs.mul(rhs);
        }

        friend T operator/(const T &lhs, const T &rhs)
        {
            return lhs.div(rhs);
        }
    };
    class Real : public NumberField<Real>
    {
    public:
        double data;

        Real(double d = 0.0) : data(d) {}

        Real add(const Real &other) const { return Real(data + other.data); }
        Real sub(const Real &other) const { return Real(data - other.data); }
        Real mul(const Real &other) const { return Real(data * other.data); }
        Real div(const Real &other) const
        {
            if (other.data == 0.0)
                throw std::invalid_argument("Division by zero");
            return Real(data / other.data);
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

        Complex add(const Complex &other) const
        {
            return Complex(real + other.real, imag + other.imag);
        }

        Complex sub(const Complex &other) const
        {
            return Complex(real - other.real, imag - other.imag);
        }

        Complex mul(const Complex &other) const
        {
            double r = real * other.real - imag * other.imag;
            double i = real * other.imag + imag * other.real;
            return Complex(r, i);
        }

        Complex div(const Complex &other) const
        {
            double denom = other.real * other.real + other.imag * other.imag;
            if (denom == 0.0)
                throw std::invalid_argument("Division by zero");

            double r = (real * other.real + imag * other.imag) / denom;
            double i = (imag * other.real - real * other.imag) / denom;
            return Complex(r, i);
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
