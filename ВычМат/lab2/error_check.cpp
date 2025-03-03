#include <iostream>
#include <cmath>
#include "horda.cpp"

double errorFunc(double x, double delta){
    return roundValue(func(x), delta);
}

double errorCheckInHorda(double a, double b, double eps, int& iterationsCount, double delta){
    double c0 = a - ((b - a) / (errorFunc(a, delta) - errorFunc(b, delta))) * errorFunc(a, delta);
    if (errorFunc(a, delta) * errorFunc(b, delta) < 0){
        if (errorFunc(c0, delta) <= eps){
            return roundValue(c0, eps);
        }
        else if (errorFunc(c0, delta) * errorFunc(a, delta) < 0){
            return horda(a, c0, eps, ++iterationsCount);
        }
        else{
            return horda(c0, b, eps, ++iterationsCount);
        }
        
    }
    else{
        std::cout << "Неверно заданный интервал!" << std::endl;
        exit(1);
    }
}