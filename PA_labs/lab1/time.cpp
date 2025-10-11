#include <iostream>
#include <algorithm>
#include <chrono>
#include "BlockMultiply.cpp"

int main(){
    BlockMultiplyMatrix obj(1408, 128);

    for (int i = 3; i <= 25; i++){
        int sum = 0;
        for (int j = 0; j < 3; j++){
            auto start = std::chrono::high_resolution_clock::now();

            obj.parallelMultiply(i);

            auto stop = std::chrono::high_resolution_clock::now();

            auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            auto seconds = duration_ms.count() / 1000;
            auto milliseconds = duration_ms.count() % 1000;

            //std::cout << "Threads count: " << i << std::endl;
            //std::cout << "Time taken by function thread " << j << " : " << seconds << "." << std::setfill('0') << std::setw(3) << milliseconds << " seconds" << std::endl;
            sum += duration_ms.count();
        }
        sum /= 3;
        std::cout << "Threads count: " << i << std::endl;
        std::cout << "AVG thread " << " : " << sum / 1000 << "." << std::setfill('0') << std::setw(3) << sum % 1000 << " seconds" << std::endl;


        sum = 0;
        for (int j = 0; j < 3; j++){
            auto start = std::chrono::high_resolution_clock::now();

            obj.parallelMultiplyFuture(i);

            auto stop = std::chrono::high_resolution_clock::now();

            auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            auto seconds = duration_ms.count() / 1000;
            auto milliseconds = duration_ms.count() % 1000;

            //std::cout << "Threads count: " << i << std::endl;
            //std::cout << "Time taken by function thread " << j << " : " << seconds << "." << std::setfill('0') << std::setw(3) << milliseconds << " seconds" << std::endl;
            sum += duration_ms.count();
        }
        sum /= 3;
        std::cout << "Threads count: " << i << std::endl;
        std::cout << "AVG future " << " : " << sum / 1000 << "." << std::setfill('0') << std::setw(3) << sum % 1000 << " seconds\n" << std::endl;

    }

    return 0;
}