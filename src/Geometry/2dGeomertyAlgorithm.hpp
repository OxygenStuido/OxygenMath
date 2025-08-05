#pragma once
#include "../Algebra/Algebra.hpp"

namespace OxygenMath
{
    class Geometry2DAlgorithm
    {
        using Vec2 = Vector2f;

    public:
        // @brief 计算两个点的距离
        // @return 返回点积结果
        inline static Real distance(const Vec2 &p1, const Vec2 &p2)
        {
            return sqrt((p1(0) - p2(0)) * (p1(0) - p2(0)) + (p1(1) - p2(1)) * (p1(1) - p2(1)));
        }
        // @brief 判断两个向量是否共线
        // @return 如果平行返回true，否则返回false
        inline static bool isCollinear(const Vec2 &p1, const Vec2 &p2)
        {
            return p1(0) * p2(1) == p1(1) * p2(0);
        }
        // @brief 判断两个向量是否垂直
        // @return 如果垂直返回true，否则返回false
        inline static bool isOrthogonal(const Vec2 &p1, const Vec2 &p2)
        {
            return p1(0) * p2(0) + p1(1) * p2(1) == Real::zero();
        }
        // @brief 计算两个向量之间的夹角(<180度)
        // @return 返回值夹角的弧度
        static Real angleBetween(const Vec2 &p1, const Vec2 &p2)
        {
            Real dotProduct = p1(0) * p2(0) + p1(1) * p2(1);
            Real normP1 = p1.norm();
            Real normP2 = p2.norm();
            if (normP1 == Real::zero() || normP2 == Real::zero())
                throw std::domain_error("Cannot compute angle with zero vector");

            return acos(dotProduct / (normP1 * normP2));
        }
        // @brief 计算三角形的面积
        // @return 返回三角形的面积
        inline static Real area(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3)
        {
            return Real(0.5) * abs((p2(0) - p1(0)) * (p3(1) - p1(1)) - (p3(0) - p1(0)) * (p2(1) - p1(1)));
        }
    };
}
