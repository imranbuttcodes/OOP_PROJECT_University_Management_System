#pragma once
#include <iostream>
#include <string>

template <typename T>
class Logger {
public:
    static void Log(std::string message, T value) {
        std::cout << "[LOG]: " << message << " " << value << std::endl;
    }
};