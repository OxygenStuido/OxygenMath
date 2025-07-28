#include <iostream>
#include <functional>
#include "OxygenMath.hpp"
using namespace OxygenMath;
static int test_pass_count = 0;
void testReal()
{
    std::cout << "=========Real test=========" << std::endl;
    Real a = 3;
    Real b = 2;
    std::cout << "a:" << a << std::endl;
    std::cout << "b:" << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << std::endl;

    std::cout << "a > b : " << (a > b) << std::endl;
    std::cout << "a >= b : " << (a >= b) << std::endl;
    std::cout << "a < b : " << (a < b) << std::endl;
    std::cout << "a <= b : " << (a <= b) << std::endl;
    std::cout << "a == b : " << (a == b) << std::endl;
    std::cout << "-a : " << -a << std::endl;
    std::cout << "=========Real test=========" << std::endl;
    test_pass_count++;
}

void testComplex()
{

    std::cout << "=========Complex test=========" << std::endl;
    Complex a(1, 3);
    Complex b(2, 3);
    std::cout << "a:" << a << std::endl;
    std::cout << "b:" << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << std::endl;
    std::cout << "=========Complex test=========" << std::endl;
    test_pass_count++;
}

void testVector()
{
    std::cout << "=========Vector test=========" << std::endl;
    Vector<Real> v1 = {Real(1), Real(2), Real(3)};
    Vector<Real> v2 = {Real(4), Real(5), Real(6)};

    std::cout << "v1:" << v1 << std::endl;
    std::cout << "v2:" << v2 << std::endl;
    std::cout << "v1 + v2 = " << v1 + v2 << std::endl;
    std::cout << "v1 - v2 = " << v1 - v2 << std::endl;
    std::cout << "v1 * 2 = " << v1 * 2 << std::endl;
    std::cout << "2 * v1 = " << 2 * v1 << std::endl;
    std::cout << "v1 dot v2  = " << v1.dot(v2) << std::endl;

    Real l2 = v1.l2_norm();
    std::cout << "L2 norm: " << l2 << std::endl; //  3.7417
    std::cout << "=========Vector test=========" << std::endl;

    test_pass_count++;
}
int main()
{
    auto a = {testReal, testComplex};
    std::vector<std::function<void()>> test_functions{testVector};
    for (const auto &func : test_functions)
    {
        func();
    }
    std::cout << "There are a total of " << static_cast<int>(test_functions.size()) << " tests\nPassed :" << test_pass_count;
    return 0;
}