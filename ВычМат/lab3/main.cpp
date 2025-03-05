#include <iostream>
#include <iomanip> // для std::setprecision
#include "newton.cpp"


int main(){


    std::cout << std::setprecision(10) << std::endl;

    int iterations = 0;
    std::cout << newton(-4, -2.5, 0.00001, iterations, 0.000001) << std::endl;
    std::cout << newton(-2.5, -2, 0.000001, iterations, 0.000001) << std::endl;
    std::cout << newton(0.01, 1, 0.000001, iterations, 0.000001) << std::endl;
    std::cout << newton(3, 4, 0.00001, iterations, 0.000001) << std::endl;

    
    return 0;
}