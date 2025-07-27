#include <iostream>
#include "OxygenMath.hpp"
using namespace OxygenMath;
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
    std::cout << "=========Real test=========" << std::endl;
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
}

int main()
{
    testReal();
    testComplex();
    return 0;
}