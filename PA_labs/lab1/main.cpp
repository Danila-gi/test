#include <iostream>
#include <algorithm>
#include <chrono>
#include "BlockMultiply.cpp"

bool checkCorrectMultyply(const std::vector<std::vector<double>>& C_blocks, const std::vector<std::vector<double>>& C_standart){
    if (C_blocks.size () != C_standart.size()){
        return false;
    }
    for (int i = 0; i < C_blocks.size(); i++){
        if (C_blocks[i].size() != C_standart[i].size()){
            return false;
        }
        for (int j = 0; j < C_blocks[i].size(); j++){
            if (abs(C_blocks[i][j] - C_standart[i][j]) >= 0.01){
                return false;
            }
        }
    }
    return true;
}

int main(){
    BlockMultiplyMatrix obj(20, 2);

    obj.parallelMultiplyFuture(6);
    obj.printResultMatrix();

    auto C_blocks = obj.getResultMatrix();

    std::cout << "=====================================\n";
    obj.clearC();

    obj.baseMultiply();
    obj.printResultMatrix();

    auto C_std = obj.getResultMatrix();

    std::cout << "Result of equal: " << checkCorrectMultyply(C_blocks, C_std) << std::endl;

    return 0;
}