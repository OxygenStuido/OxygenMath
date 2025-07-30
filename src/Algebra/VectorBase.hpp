#pragma once
// TODO : 实现VectorN与Vector的基类 使用CRTP设计模式，统一通用运算
#pragma once
#include <array>
#include <vector>
#include <cmath>
#include <type_traits>
#include "NumberField.hpp"
#include "../Constants.hpp"

namespace OxygenMath
{

    /*! \brief 向量CRTP基类
     * \tparam Derived 派生类类型
     * \tparam T 元素类型
     */
    template <typename Derived, typename T>
    class VectorBase
    {
    public:
        size_t size() const { return static_cast<const Derived *>(this)->size(); }
        T operator[](size_t i) const { return static_cast<const Derived *>(this)->operator[](i); }
        T &operator[](size_t i) { return static_cast<Derived *>(this)->operator[](i); }
        Derived operator+(const Derived &other) const
        {
            Derived result;
            for (size_t i = 0; i < size(); ++i)
                result[i] = (*this)[i] + other[i];
            return result;
        }

        T dot(const Derived &other) const
        {
            T sum = T::zero();
            for (size_t i = 0; i < size(); ++i)
                sum += (*this)[i] * other[i];
            return sum;
        }
    };
}