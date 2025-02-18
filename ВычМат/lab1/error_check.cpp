#include <iostream>
#include <cmath>
#include "bisection.cpp"

double errorFunc(double x, double delta){
    return roundValue(func(x), delta);
}

double errorCheckInBisection(double a, double b, double eps, int& iterationsCount, double delta){
    double e = (a + b) / 2;
    if (errorFunc(a, delta) * errorFunc(b, delta) < 0){
        if (errorFunc(e, delta) == 0 || (b - a) < 2 * eps){
            return roundValue(e, eps);
        }
        else if (errorFunc(e, delta) * errorFunc(a, delta) < 0){
            return errorCheckInBisection(a, e, eps, ++iterationsCount, delta);
        }
        else{
            return errorCheckInBisection(e, b, eps, ++iterationsCount, delta);
        }
        
    }
    else{
        std::cout << errorFunc(a, delta) << " " << errorFunc(b, delta) << " ";
        std::cout << "Incorrect range! Exit: ";
        return -1;
    }
}