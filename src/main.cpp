#include <iostream>
#include "OxygenMath.hpp"
using namespace OxygenMath;
int main()
{
    real r1(5.0);
    real r2(3.0);

    std::cout << "r1: " << r1 << std::endl;
    std::cout << "r2: " << r2 << std::endl;

    Vector<real> vec1(3);
    vec1[0] = 1;
    vec1[1] = 2;
    vec1[2] = 3;

    Vector<real> vec2(3);
    vec2[0] = 4;
    vec2[1] = 5;
    vec2[2] = 6;

    Vector<real> sum = vec1 + vec2;
    Vector<real> difference = vec1 - vec2;
    Vector<real> scaled1 = r2 * vec1;
    Vector<real> scaled2 = vec1 * r2;

    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << difference << std::endl;
    std::cout << "left Scaled: " << scaled1 << std::endl;
    std::cout << "right Scaled: " << scaled2 << std::endl;
    vec1.Transpose();
    std::cout << "vec1 transpose first: " << vec1 << std::endl;
    vec1.Transpose();
    std::cout << "vec1 transpose second: " << vec1 << std::endl;

    return 0;
}