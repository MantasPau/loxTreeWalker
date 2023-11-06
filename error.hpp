#pragma once

#include <iostream>
#include <string>

class Error
{
public:
    static void Throw(int line, std::string message) {
        Report(line, "", message);
    }
    static bool IsError() {
        return hadError;
    }
    static void Reset() {
        hadError = false;
    }
private:
    static void Report(int line, std::string where, std::string message) {
        std::cout << "[line " << line << "] Error" << where << ": " << message << std::endl;
        hadError = true;
    }
    static bool hadError;
};

bool Error::hadError = false;