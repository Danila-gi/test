#include <iostream>
#include <cmath>

double func(double x){
    return pow(x, 4) - 13 * pow(x, 2) + 36 - 1 / x;
}

double func_1(double x){
    return (4 * pow(x, 5) - 26 * pow(x, 3) + 1) / (pow(x, 2));
}

double roundValue(double x, double delta){
    if (x > 0)
        return delta * double(x / delta + 0.5);
    else
        return delta * double(x / delta - 0.5);
}

double deltaFunc(double x, double delta){
    return roundValue(func(x), delta);
}

double deltaFunc_1(double x, double delta){
    return roundValue(func_1(x), delta);
}

double findX(double left, double right, double delta){
    if (deltaFunc(left, delta) * deltaFunc(right, delta) > 0 || left > right){
        std::cout << "Incorrect data" << std::endl;
        exit(1);
    }
    for (double x = left; x <= right; x = x + delta){
        if (deltaFunc(x, delta) * deltaFunc_1(x, delta) > 0)
            return x;
    }
}

double newton(double left, double right, double eps, int& iterationsCount, double delta){
    double x = findX(left, right, delta);
    double x_next;
    //std::cout << x << " " << deltaFunc(x, delta) << " " << deltaFunc_1(x, delta) << std::endl;
    x_next = x - deltaFunc(x, delta) / deltaFunc_1(x, delta);
    iterationsCount++;

    while (abs(x_next - x) >= eps){
        if (deltaFunc(x_next, delta) == 0)
            return x_next;
        if (deltaFunc_1(x_next, delta) == 0){
            std::cout << "Derivative is zero!" << std::endl;
            return -1;
        }
        x = x_next;
        x_next = x - deltaFunc(x, delta) / deltaFunc_1(x, delta);
        iterationsCount++;
    }
    return x_next;
}