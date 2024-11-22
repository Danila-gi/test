#include "../headers/FileWrapper.h"

FileWrapper::FileWrapper(const std::string& filename, std::ios::openmode mode) : file(filename, mode) {
    if (!file)
        throw std::runtime_error("File open failure");
}

FileWrapper::~FileWrapper() {
    if (file.is_open())
        file.close();
}

template<>
void FileWrapper::write(const int& data) {
    if (!file.is_open() || !file.good()) {
        throw std::runtime_error("File not opened in output mode");
    }
    file << data;
}

template<>
void FileWrapper::write(const char& data) {
    if (!file.is_open() || !file.good()) {
        throw std::runtime_error("File not opened in output mode");
    }
    file << data;
}

template<>
void FileWrapper::read(int& data) {
    if (!file.is_open() || !file.good()) {
        throw std::runtime_error("File not opened in input mode");
    }
    file >> data;
}