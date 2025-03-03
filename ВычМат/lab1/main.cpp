#include <iostream>
#include <iomanip> // для std::setprecision
#include "error_check.cpp"

int main(){
    int iterations = 0;
    std::cout << bisection(0, 1, 0.01, iterations) << std::endl;
    
    return 0;
}