#include <iostream>
#include <fstream>
#include <string>

int main() {
    const std::string file_path = "/home/user1/secret_file.txt";

    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Error with open file" << file_path << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();

    return 0;
}
