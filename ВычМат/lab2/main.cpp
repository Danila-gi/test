#include <iostream>
#include <iomanip> // для std::setprecision
#include "horda.cpp"

double f(double x){
    return 1.0 / abs((4 * pow(x, 5) - 26 * pow(x, 4) + 1) / (pow(x, 2)));
}

int main(){



    /*int iterations = 0;

    std::cout << std::setprecision(10) << std::endl;

    for (double delta=0.1; delta >= 0.000001; delta = delta / 10){
        for (double eps=0.1; eps >= 0.000001; eps = eps / 10){
            std::cout << "delta=" << delta << " eps=" << eps << " : " << horda(-4, -2.5, eps, iterations, delta) << std::endl;
        }
    }*/

    /*int iterations = 0;
    std::cout << horda(-4, -2.5, 0.001, iterations, 0.000001) << " - " << func(-2.988647143) << std::endl;
    std::cout << horda(-2.5, -2, 0.1, iterations, 0.000001) << " - " << func(-2.025258857) << std::endl;
    std::cout << horda(0.01, 1, 0.01, iterations, 0.000001) << " - " << func(0.02779310654) << std::endl;
    std::cout << horda(3, 4, 0.00001, iterations, 0.000001) << " - " << func(3.010907432) * 100 << std::endl;*/

    
    return 0;
}