#pragma once
#include "NumberField.hpp"
namespace OxygenMath
{
    Real sqrt(const Real &num)
    {
        if (num.data < 0.0)
            throw std::domain_error("Square root of negative number");
        return Real(std::sqrt(num.data));
    }

    Complex sqrt(const Complex &num)
    {
        double r = std::sqrt(std::sqrt(num.real * num.real + num.imag * num.imag));
        double theta = std::atan2(num.imag, num.real) / 2.0;
        return Complex(r * std::cos(theta), r * std::sin(theta));
    }

    
}