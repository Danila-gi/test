#ifndef WRAPPER_H
#define WRAPPER_H

#include <iostream>
#include <fstream>

class FileWrapper {
    std::fstream file;
public:
    FileWrapper(const std::string& filename, std::ios::openmode mode);

    ~FileWrapper();

    template <typename T>
    void write(const T& data);

    template <typename T>
    bool read(T& data);

    bool isEOF() const;

    void rewind();
};

#endif
