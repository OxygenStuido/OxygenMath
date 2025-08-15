#pragma once
#include "../Algebra/Algebra.hpp"

namespace OxygenMath
{
    namespace Geometry2DAlgorithm
    {
        using Vec2 = Vector2f;

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
         * @brief 将二维向量绕原点旋转指定角度
         * @param point 待旋转的二维向量
         * @param radius 旋转角度（弧度制）
         * @return 旋转后的二维向量
         */
        static Vec2 Rotate(const Vec2 &point, const Real &radius)
        {
            Real cos_ = cos(radius);
            Real sin_ = sin(radius);
            return Vec2{point(0) * cos_ - point(1) * sin_,
                        point(0) * sin_ + point(1) * cos_};
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
        static inline Real tirangleArea(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3)
        {
            return Real(0.5) * abs((p2(0) - p1(0)) * (p3(1) - p1(1)) - (p3(0) - p1(0)) * (p2(1) - p1(1)));
        }

        /**
         * @brief 获取三角形的周长
         *
         * 通过计算三角形三条边的长度来获取三角形的周长。
         *
         * @param p1 第1个顶点
         * @param p2 第2个顶点
         * @param p3 第3个顶点
         * @return 获取三角形的周长
         */
        static inline Real tiranglePerimeter(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3)
        {
            return distance(p1, p2) + distance(p2, p3) + distance(p3, p1);
        }

        /**
         * @brief 计算点到直线的距离
         *
         * 通过给定直线上的两个点确定一条直线，计算指定点到该直线的垂直距离。
         * 使用直线的一般式方程 Ax + By + C = 0 来计算距离。
         *
         * @param point 待计算距离的点坐标
         * @param linePoint1 直线上的第一个点坐标
         * @param linePoint2 直线上的第二个点坐标
         * @return 返回点到直线的垂直距离，结果为非负实数
         */
        static Real pointToLineDistance(const Vec2 &point, const Vec2 &linePoint1, const Vec2 &linePoint2)
        {
            Real A = linePoint2(1) - linePoint1(1);
            Real B = linePoint1(0) - linePoint2(0);
            Real C = linePoint2(0) * linePoint1(1) - linePoint1(0) * linePoint2(1);

            return abs(A * point(0) + B * point(1) + C) / sqrt(A * A + B * B);
        }
        /**
         * @brief 获取线段交点
         *
         * @param p1
         * @param p2
         * @param p3
         * @param p4
         * @return Vec2
         */
        static Vec2 getLineIntersection(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Vec2 &p4)
        {
            Real A1 = p2(1) - p1(1);
            Real B1 = p1(0) - p2(0);
            Real C1 = A1 * p1(0) + B1 * p1(1);

            Real A2 = p4(1) - p3(1);
            Real B2 = p3(0) - p4(0);
            Real C2 = A2 * p3(0) + B2 * p3(1);

            Real det = A1 * B2 - A2 * B1;
            if (det == Real::zero())
                throw std::domain_error("Lines are parallel, no intersection");

            Real x = (B2 * C1 - B1 * C2) / det;
            Real y = (A1 * C2 - A2 * C1) / det;
            return Vec2{x, y};
        }

        /**
         * @brief 判断两条线段是否相交
         *
         * 使用线段的参数方程和行列式方法来判断两条线段是否相交。
         *
         * @param p1 线段1的起点
         * @param p2 线段1的终点
         * @param p3 线段2的起点
         * @param p4 线段2的终点
         * @return true 如果两条线段相交
         * @return false 如果两条线段不相交
         */
        static bool lineIntersection(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Vec2 &p4)
        {
            Real A1 = p2(1) - p1(1);
            Real B1 = p1(0) - p2(0);
            Real C1 = A1 * p1(0) + B1 * p1(1);

            Real A2 = p4(1) - p3(1);
            Real B2 = p3(0) - p4(0);
            Real C2 = A2 * p3(0) + B2 * p3(1);

            Real det = A1 * B2 - A2 * B1;
            return det != Real::zero();
        }

        /**
         * @brief 判断两个圆是否相交
         * @param p1 第一个圆的圆心坐标
         * @param r1 第一个圆的半径
         * @param p2 第二个圆的圆心坐标
         * @param r2 第二个圆的半径
         * @return 如果两个圆相交则返回true，否则返回false
         */
        static inline bool circleIntersection(const Vec2 &p1, Real r1, const Vec2 &p2, Real r2)
        {
            return distance(p1, p2) <= r1 + r2;
        }

        /**
         * @brief 检测两个轴对齐矩形是否相交
         *
         * 该函数通过比较两个矩形的边界框来判断它们是否相交。
         * 第一个矩形由点p1和p2定义，第二个矩形由点p3和p4定义。
         *
         * @param p1 第一个矩形的第一个顶点坐标
         * @param p2 第一个矩形的第二个顶点坐标
         * @param p3 第二个矩形的第一个顶点坐标
         * @param p4 第二个矩形的第二个顶点坐标
         * @return 如果两个矩形相交返回true，否则返回false
         */
        static bool boxIntersection(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Vec2 &p4)
        {
            Real x1 = std::min(p1(0), p2(0)), x2 = std::max(p1(0), p2(0));
            Real y1 = std::min(p1(1), p2(1)), y2 = std::max(p1(1), p2(1));
            return x1 <= std::max(p3(0), p4(0)) && x2 >= std::min(p3(0), p4(0)) &&
                   y1 <= std::max(p3(1), p4(1)) && y2 >= std::min(p3(1), p4(1));
        }

        /**
         * @brief 检测一个点是否在给定的轴对齐矩形内
         *
         * @param point 待检测的点坐标
         * @param p1 矩形的第一个顶点坐标
         * @param p2 矩形的第二个顶点坐标
         * @return 如果点在矩形内返回true，否则返回false
         */
        static inline bool pointInBox(const Vec2 &point, const Vec2 &p1, const Vec2 &p2)
        {
            return point(0) >= std::min(p1(0), p2(0)) && point(0) <= std::max(p1(0), p2(0)) &&
                   point(1) >= std::min(p1(1), p2(1)) && point(1) <= std::max(p1(1), p2(1));
        }

        /**
         * @brief 检测一个点是否在给定的圆内
         *
         * @param point 待检测的点坐标
         * @param center 圆的圆心坐标
         * @param radius 圆的半径
         * @return 如果点在圆内返回true，否则返回false
         */
        static inline bool pointInCircle(const Vec2 &point, const Vec2 &center, Real radius)
        {
            return distance(point, center) <= radius;
        }

    } // namespace Geometry2DAlgorithm

} // namespace OxygenMath
