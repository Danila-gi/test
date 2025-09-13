#include <iostream>
#include <algorithm>
#include <chrono>
#include "BlockMultiply.cpp"

int main(){
    BlockMultiplyMatrix obj(1000, 10);

    auto start = std::chrono::high_resolution_clock::now();

    obj.parallelMultiply(28);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    auto seconds = duration_ms.count() / 1000;
    auto milliseconds = duration_ms.count() % 1000;

    std::cout << "Time taken by function: " << seconds << "." << std::setfill('0') << std::setw(3) << milliseconds << " seconds" << std::endl;

    return 0;
}