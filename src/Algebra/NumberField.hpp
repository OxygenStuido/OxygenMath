#pragma once
#include <iostream>
namespace OxygenMath
{
    class real
    {
    public:
        double data;
        real() : data(0.0) {} // Default constructor
        real(const double &a) : data(a) {}

        static real zero() { return real(0.0); }
        static real identity() { return real(1.0); }

        friend std::ostream &operator<<(std::ostream &os, const real &c)
        {
            os << c.data;
            return os;
        }

        // Overload operators for arithmetic operations
        real operator+(const real &other) const { return real(data + other.data); }
        real operator-(const real &other) const { return real(data - other.data); }
        real operator*(const real &other) const { return real(data * other.data); }
        real operator/(const real &other) const 
        { 
            if (other.data != 0.0) {
                return real(data / other.data);
            } else {
                throw std::invalid_argument("Division by zero");
            }
        }
    };
    // NumberField
    // T belongs to any number field, that is, it is closed to addition, subtraction, multiplication and division
    // For example:
    // For any T_1 T_2 belongs to P
    // T_1+T_2 also belongs to P; T_1-T_2 also belongs to P ; T_1*T_2 also belongs to P ; T_1/T_2 also belongs to P ;
    template <typename T>
    concept Field = requires(T a, T b) {
        { a + b } -> std::same_as<T>;
        { a - b } -> std::same_as<T>;
        { a * b } -> std::same_as<T>;
        { a / b } -> std::same_as<T>;
        { T(0) } -> std::same_as<T>;
        { T(1) } -> std::same_as<T>;
    };
}
