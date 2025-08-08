#include <iostream>
#include <functional>
#include <random>
#include "OxygenMath.hpp"

using namespace OxygenMath;
static int test_pass_count = 0;
void testMatrix();
void testVector();
void test2dGeometry();
void testLUP();
void myTest();
void testInverseAndDeterminant();
int main()
{
    auto test_funnctions = {testMatrix, test2dGeometry, testVector, myTest};
    std::vector<std::function<void()>> test_functions{testLUP, testInverseAndDeterminant};
    for (const auto &func : test_functions)
    {
        func();
    }
    std::cout << "There are a total of " << static_cast<int>(test_functions.size()) << " tests\nPassed :" << test_pass_count;
    return 0;
}
void test2dGeometry()
{
    std::cout << "=========2D Geometry test=========" << std::endl;

    Vector2f p1{0, 3};
    Vector2f p2{4, 0};

    Real dist = Geometry2DAlgorithm::distance(p1, p2);
    std::cout << "Distance between p1 and p2: " << dist << std::endl;

    std::cout << "=========2D Geometry test=========" << std::endl;
}
void testMatrix()
{
    std::cout << "=========Matrix test=========" << std::endl;

    // 构造2x2矩阵
    MatrixNM<Real, 2, 2> m1{{{1.0, 2.0}, {3.0, 4.0}}};
    MatrixNM<Real, 2, 2> m2{{{5.0, 6.0}, {7.0, 8.0}}};

    std::cout << "Matrix m1:\n"
              << m1 << "\n";
    std::cout << "Matrix m2:\n"
              << m2 << "\n";

    // 加法
    auto m_add = m1 + m2;
    std::cout << "m1 + m2:\n"
              << m_add << "\n";

    // 减法
    auto m_sub = m1 - m2;
    std::cout << "m1 - m2:\n"
              << m_sub << "\n";

    // 乘法
    auto m_mul = m1 * m2;
    std::cout << "m1 * m2:\n"
              << m_mul << "\n";

    // 标量乘法
    auto m_scalar_mul = m1 * Real(2.0);
    std::cout << "m1 * 2.0:\n"
              << m_scalar_mul << "\n";

    // 标量乘法（反向）
    auto m_scalar_mul2 = Real(2.0) * m1;
    std::cout << "2.0 * m1:\n"
              << m_scalar_mul2 << "\n";

    m1 = m_mul;
    std::cout << "After assignment, m1:\n"
              << m1 << "\n";

    std::cout << "=========Matrix test=========" << std::endl;
    test_pass_count++;
}
void testVector()
{
    std::cout << "=========Vector test=========" << std::endl;

    OxygenMath::VectorN<OxygenMath::Real, 3> v1{1.0, 2.0, 3.0};
    std::cout << "Vector v1:\n " << v1 << std::endl;
    OxygenMath::VectorN<OxygenMath::Real, 3> v2{4.0, 5.0, 6.0};

    auto v1_v2_add = v1 + v2; // 向量加法
    std::cout << "v1 + v2:\n " << v1_v2_add << std::endl;

    auto v1_v2_sub = v1 - v2; // 向量减法
    std::cout << "v1 - v2:\n " << v1_v2_sub << std::endl;
    auto v1_v2_dot = v1.dot(v2); // 向量点积
    std::cout << "v1 dot v2:\n " << v1_v2_dot << std::endl;
    auto v1_v2_cross = v1.cross(v2); // 向量叉积
    std::cout << "v1 cross v2:\n " << v1_v2_cross << std::endl;
    auto v1_norm = v1.norm(); // 向量范数
    std::cout << "v1 norm:\n " << v1_norm << std::endl;
    auto v1_normalized = v1.normalize(); // 向量归一化
    std::cout << "v1 normalized:\n " << v1_normalized << std::endl;
    // 测试矩阵
    OxygenMath::MatrixNM<OxygenMath::Real, 3, 3>
        mat{{1.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 3.0}};
    std::cout << "Matrix mat:\n"
              << mat << std::endl;

    // 测试各种运算
    auto v3 = 2.0 * v1; // 标量乘向量
    std::cout << "2.0 * v1:\n " << v3 << std::endl;
    auto v4 = mat * v2; // 矩阵乘向量
    std::cout << "mat * v2:\n " << v4 << std::endl;

    auto m1 = 0.5 * mat; // 标量乘矩阵
    std::cout << "0.5 * mat:\n"
              << m1 << std::endl;
    auto m2 = mat * mat; // 矩阵乘法
    std::cout << "mat * mat:\n"
              << m2 << std::endl;

    std::cout << "=========Vector test=========" << std::endl;
    test_pass_count++;
}

void testLUP()
{
    std::cout << "=========LUPTest=========" << std::endl;
    constexpr size_t N = 100;
    std::mt19937 gen(1); // 固定种子保证可复现
    std::uniform_real_distribution<double> dis(-10.0, 10.0);

    for (int t = 0; t < 100; ++t) // 生成100组测试
    {
        MatrixNM<Real, N, N> A;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                A(i, j) = dis(gen);

        auto PLU = linalg::luDecomposition(A);

        auto PA = PLU.P * A;
        auto LU = PLU.L * PLU.U;

        bool ok = true;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                if (abs(PA(i, j) - LU(i, j)) > Constants::epsilon)
                    ok = false;

        std::cout << "Test #" << t + 1 << ": " << (ok ? "PASS" : "FAIL") << std::endl;
        if (!ok)
        {
            std::cout << "A:\n"
                      << A << "\n";
            std::cout << "P*A:\n"
                      << PA << "\n";
            std::cout << "L*U:\n"
                      << LU << "\n";
        }
    }
    std::cout << "=========LUPTest End=========" << std::endl;
    test_pass_count++;
}
void myTest()
{
    std::cout << "=========My Test=========" << std::endl;
    MatrixNM<Real, 3, 3> m1{{{1.0, 2.0, 3.0}, {4.0, 1.0, 6.0}, {7.0, 8.0, 9.0}}};
    std::cout << linalg::determinant(m1) << std::endl;
    MatrixNM<Real, 2, 2> m2{{{1.0, 2.0}, {3.0, 4.0}}};
    std::cout << linalg::determinant(m2) << std::endl;
    MatrixNM<Real, 5, 5> m3{{{0, 2, 1, 3, 4},
                             {1, 3, 4, 2, 1},
                             {2, 1, 3, 4, 2},
                             {3, 4, 2, 1, 3},
                             {4, 5, 1, 2, 1}}};
    std::cout << m3 << std::endl;
    auto PLU = linalg::luDecomposition(m3);
    std::cout << "L:\n"
              << PLU.L << std::endl;
    std::cout << "U:\n"
              << PLU.U << std::endl;
    std::cout << "P:\n"
              << PLU.P << std::endl;
    std::cout << "P*A:\n";
    std::cout << PLU.P * m3 << std::endl; // P * A
    std::cout << "L * U:\n";
    std::cout << PLU.L * PLU.U << std::endl; // L * U

    std::cout << linalg::determinant(m3) << std::endl;
    // std::cout << linalg::inverse(m3) << std::endl;
    std::cout << "=========My Test end=========" << std::endl;
}

void testInverseAndDeterminant()
{
    std::cout << "=========Inverse & Determinant Test=========" << std::endl;
    constexpr size_t N = 5;
    std::mt19937 gen(123);
    std::uniform_real_distribution<double> dis(-10.0, 10.0);

    for (int t = 0; t < 10; ++t)
    {
        MatrixNM<Real, N, N> A;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                A(i, j) = dis(gen);

        Real det = linalg::determinant(A);
        bool singular = abs(det) < Constants::epsilon;

        std::cout << "Test #" << t + 1 << " det=" << det << std::endl;

        if (!singular)
        {
            auto invA = linalg::inverse(A);
            auto prod = A * invA;

            // 检查是否接近单位矩阵
            bool ok = true;
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < N; ++j)
                {
                    Real expected = (i == j) ? 1.0 : 0.0;
                    if (abs(prod(i, j) - expected) > Constants::epsilon)
                        ok = false;
                }
            std::cout << "Inverse test: " << (ok ? "PASS" : "FAIL") << std::endl;
            if (!ok)
            {
                std::cout << "A:\n"
                          << A << "\n";
                std::cout << "A^-1:\n"
                          << invA << "\n";
                std::cout << "A * A^-1:\n"
                          << prod << "\n";
            }
        }
        else
        {
            std::cout << "Matrix is singular, skip inverse test." << std::endl;
        }
    }
    std::cout << "=========Inverse & Determinant Test End=========" << std::endl;
    test_pass_count++;
}