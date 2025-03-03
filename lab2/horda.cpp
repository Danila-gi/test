#include <iostream>
#include <cmath>

double func(double x){
    return pow(x, 4) - 13 * pow(x, 2) + 36 - 1 / x;
}

double roundValue(double x, double delta){
    if (x > 0)
        return delta * long(x / delta + 0.5);
    else
        return delta * long(x / delta - 0.5);
}

double deltaFunc(double x, double delta){
    return roundValue(func(x), delta);
}

double horda(double a, double b, double eps, int& iterationsCount, double delta){
    double c0 = a - ((b - a) / (deltaFunc(b, delta) - deltaFunc(a, delta))) * deltaFunc(a, delta);
    if (deltaFunc(a, delta) * deltaFunc(b, delta) < 0){
        //std::cout << fabs(deltaFunc(c0, delta)) << std::endl;
        if (fabs(deltaFunc(c0, delta)) < eps){
            return c0;
        }
        else if (deltaFunc(c0, delta) * deltaFunc(a, delta) < 0){
            return horda(a, c0, eps, ++iterationsCount, delta);
        }
        else{
            return horda(c0, b, eps, ++iterationsCount, delta);
        }
        
    }
    else{
        std::cout << "Неверно заданный интервал!" << std::endl;
        exit(1);
    }
}