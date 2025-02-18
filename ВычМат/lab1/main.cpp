#include <iostream>
#include <iomanip> // для std::setprecision
#include "error_check.cpp"

int main(){
    int iterations = 0;
    std::cout << "Check for [-4, -2.5]" << std::endl;
    std::cout << std::fixed << std::setprecision(6) << bisection(-4, -2.5, 0.000001, iterations) << std::endl;
    for (int i = 1; i <= 6; i++){
        for (int j = 1; j <= 6; j++){
            std::cout << "delta=" << 1/pow(10, i) << " and eps=" << 1/pow(10, j) << " : ";
            std::cout << std::fixed << std::setprecision(6) << errorCheckInBisection(-4, -2.5, 1/pow(10, j), iterations, 1/pow(10, i)) << std::endl;
        }
    }
    return 0;
}