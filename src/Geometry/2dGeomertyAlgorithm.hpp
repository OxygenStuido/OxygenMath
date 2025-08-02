#pragma once
#include "../Algebra/Algebra.hpp"

namespace OxygenMath
{
    using Vec2 = Vector2f;
    class Geometry2DAlgorithm
    {
    public:
        static Real distance(const Vec2 &p1, const Vec2 &p2)
        {
            Real dx = p1(0) - p2(0);
            Real dy = p1(1) - p2(1);
            return sqrt(dx * dx + dy * dy);
        }
    };
}
