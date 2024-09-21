#include <iostream>
#include <map>
#include <vector>

int main(){
    std::map<std::string, std::vector<int>> products;
    products["bread"] = {34, 56};
    products["milk"] = {80, 1, 2};
    products["apple"] = {55, 88, 99, 0};

    for (int n : products["bread"])
        std::cout << n << std::endl;
    return 0;
}