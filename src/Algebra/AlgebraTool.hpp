#pragma once
#include "NumberField.hpp"
namespace OxygenMath
{
    /**
     * @brief 计算实数的平方根。
     * @param num 底数。
     * @return 实数的平方根
     */
    Real sqrt(const Real &num)
    {
        if (num.data < 0.0)
            throw std::domain_error("Square root of negative number");
        return Real(std::sqrt(num.data));
    }
    /**
     * @brief 计算实数的绝对值
     * @param num 底数
     * @return 实数的绝对值
     */
    inline Real abs(const Real &num)
    {
        return Real(std::abs(num.data));
    }

    /////////////////////////////////////////////////////////////
    // 三角函数                                             start
    /////////////////////////////////////////////////////////////
    /**
     * @brief 计算实数的余弦值
     * @param angle 弧度制角度
     * @return 实数的余弦值
     */
    inline Real cos(const Real &angle)
    {
        return Real(std::cos(angle.data));
    }
    /**
     * @brief 计算实数的正弦值
     * @param angle 弧度制角度
     * @return 实数的正弦值
     */
    inline Real sin(const Real &angle)
    {
        return Real(std::sin(angle.data));
    }
    /**
     * @brief 计算实数的正切值
     * @param angle 弧度制角度
     * @return 实数的正切值
     */
    Real tan(const Real &angle)
    {
        if (std::cos(angle.data) == 0.0)
            throw std::domain_error("Tangent undefined for angle with cos = 0");
        return Real(std::tan(angle.data));
    }
    /**
     * @brief 计算实数的反余弦值
     * @param value 输入值，必须在[-1, 1]范围内
     * @return 实数的反余弦值
     */
    Real acos(const Real &value)
    {
        if (value.data < -1.0 || value.data > 1.0)
            throw std::domain_error("acos undefined for value outside [-1, 1]");
        return Real(std::acos(value.data));
    }
    /**
     * @brief 计算实数的反正弦值
     * @param value 输入值，必须在[-1, 1]范围内
     * @return 实数的反正弦值
     */
    Real asin(const Real &value)
    {
        if (value.data < -1.0 || value.data > 1.0)
            throw std::domain_error("asin undefined for value outside [-1, 1]");
        return Real(std::asin(value.data));
    }
    /**
     * @brief 计算实数的反正切值
     * @param value 输入值
     * @return 实数的反正切值
     */
    inline Real atan(const Real &value)
    {
        return Real(std::atan(value.data));
    }
    /**
     * @brief 计算实数的双曲正弦值
     * @param value 输入值
     * @return 实数的双曲正弦值
     */
    inline Real sinh(const Real &value)
    {
        return Real(std::sinh(value.data));
    }
    /**
     * @brief 计算实数的双曲余弦值
     * @param value 输入值
     * @return 实数的双曲余弦值
     */
    inline Real cosh(const Real &value)
    {
        return Real(std::cosh(value.data));
    }
    /**
     * @brief 计算实数的双曲正切值
     * @param value 输入值
     * @return 实数的双曲正切值
     */
    inline Real tanh(const Real &value)
    {
        return Real(std::tanh(value.data));
    }
    /////////////////////////////////////////////////////////////
    // 三角函数                                               end
    /////////////////////////////////////////////////////////////

    /**
     * @brief 计算实数的指数值
     * @param exponent 指数
     * @return 实数的指数值
     */
    inline Real exp(const Real &exponent)
    {
        return Real(std::exp(exponent.data));
    }
    /**
     * @brief 计算实数的对数值
     * @param value 输入值，必须大于0
     * @return 实数的对数值
     */
    Real log(const Real &value)
    {
        if (value.data <= 0.0)
            throw std::domain_error("Logarithm undefined for non-positive values");
        return Real(std::log(value.data));
    }
    /**
     * @brief 计算实数的自然对数值
     * @param value 输入值，必须大于0
     * @return 实数的自然对数值
     */
    Real log10(const Real &value)
    {
        if (value.data <= 0.0)
            throw std::domain_error("Logarithm undefined for non-positive values");
        return Real(std::log10(value.data));
    }

    /**
     * @brief 计算复数的平方根
     * @param num 复数
     * @return 复数的平方根
     */
    Complex sqrt(const Complex &num)
    {
        double r = std::sqrt(std::sqrt(num.real * num.real + num.imag * num.imag));
        double theta = std::atan2(num.imag, num.real) / 2.0;
        return Complex(r * std::cos(theta), r * std::sin(theta));
    }

}