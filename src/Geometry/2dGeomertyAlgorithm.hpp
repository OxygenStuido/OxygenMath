#pragma once
#include "../Algebra/Algebra.hpp"

namespace OxygenMath
{
    class Geometry2DAlgorithm
    {
        using Vec2 = Vector2f;

    public:
        /**
         * @brief 计算两个二维点之间的欧几里得距离
         *
         * 该函数使用欧几里得距离公式计算两个二维向量点p1和p2之间的直线距离
         *
         * @param p1 第一个二维点
         * @param p2 第二个二维点
         * @return 返回两个点之间的欧几里得距离
         */
        static inline Real distance(const Vec2 &p1, const Vec2 &p2)
        {
            return sqrt((p1(0) - p2(0)) * (p1(0) - p2(0)) + (p1(1) - p2(1)) * (p1(1) - p2(1)));
        }
        /**
         * @brief 判断两个二维向量是否共线
         *
         * 通过计算两个向量的叉积来判断是否共线。如果叉积为0，则两向量共线。
         * 叉积公式：p1(0) * p2(1) - p1(1) * p2(0) = 0
         *
         * @param p1 第一个二维向量
         * @param p2 第二个二维向量
         * @return true 如果两个向量共线
         * @return false 如果两个向量不共线
         */
        static inline bool isCollinear(const Vec2 &p1, const Vec2 &p2)
        {
            return p1(0) * p2(1) == p1(1) * p2(0);
        }
        /**
         * @brief 判断两个二维向量是否正交（垂直）
         *
         * 通过计算两个向量的数量积（点积）来判断是否正交。
         * 如果数量积为0，则两向量正交。
         *
         * @param p1 第一个二维向量
         * @param p2 第二个二维向量
         * @return true 如果两向量正交
         * @return false 如果两向量不正交
         */
        static inline bool isOrthogonal(const Vec2 &p1, const Vec2 &p2)
        {
            return p1(0) * p2(0) + p1(1) * p2(1) == Real::zero();
        }
        
        /**
         * @brief 计算两个二维向量的角度
         *
         * 通过计算两个向量的点积和两个向量的模长来计算两个向量的角度。
         *
         * @param p1 第1个二维向量
         * @param p2 第2个二维向量
         * @return 返回两个向量的角度
         */
        static Real angleBetween(const Vec2 &p1, const Vec2 &p2)
        {
            Real dotProduct = p1(0) * p2(0) + p1(1) * p2(1);
            Real normP1 = p1.norm();
            Real normP2 = p2.norm();
            if (normP1 == Real::zero() || normP2 == Real::zero())
                throw std::domain_error("Cannot compute angle with zero vector");

            return acos(dotProduct / (normP1 * normP2));
        }
        
        /**
         * @brief 计算三角形的面积
         *
         * 使用向量叉积公式计算三角形面积：
         * area = 0.5 * |(p2 - p1) x (p3 - p1)|
         *
         * @param p1 第一个顶点
         * @param p2 第二个顶点
         * @param p3 第三个顶点
         * @return 返回三角形的面积
         */
        static inline Real area(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3)
        {
            return Real(0.5) * abs((p2(0) - p1(0)) * (p3(1) - p1(1)) - (p3(0) - p1(0)) * (p2(1) - p1(1)));
        }
    };
}
