#include <iostream>
#include <cmath>

double func(double x){
    return pow(x, 4) - 13 * pow(x, 2) + 36 - 1 / x;
}

double roundValue(double x, double delta){
    return round(x / delta) * delta;
}

double bisection(double a, double b, double eps, int& iterationsCount){
    double e = (a + b) / 2;
    if (func(a) * func(b) < 0){
        if (func(e) == 0 || (b - a) < 2 * eps){
            return roundValue(e, eps);
        }
        else if (func(e) * func(a) < 0){
            return bisection(a, e, eps, ++iterationsCount);
        }
        else{
            return bisection(e, b, eps, ++iterationsCount);
        }
        
    }
    else{
        std::cout << "Неверно заданный интервал!" << std::endl;
        exit(1);
    }
}