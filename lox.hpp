#pragma once

#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <list>

#include <scanner.hpp>
#include <token.hpp>
#include <error.hpp>

class Lox
{
public:
    Lox();
    void RunFile(char * fileName);
    void RunPrompt();
    
private:
    void Run(const std::string& script);
    Error err;
};

Lox::Lox()
{
    err.Reset();
}

void Lox::RunFile(char * fileName)
{
    std::ifstream fs(fileName);
    if (fs.is_open()) {
        std::string script;
        script.assign(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());
        Lox::Run(script);
        if (err.IsError()) exit(EXIT_FAILURE);
    }
    else {
        //throw error here
        std::cout << "Error opening file" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Lox::RunPrompt()
{
    for (;;) {
        std::cout << "Lox::>";
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) break;
        Run(line);
    }
}

void Lox::Run(const std::string& script)
{
    Scanner scanner(script);
    std::list<Token> tokens;
    tokens = scanner.ScanTokens();

    std::list<Token>::iterator tIt;
    for (tIt = tokens.begin(); tIt != tokens.end(); tIt++)
    {
        std::cout << *tIt << std::endl;
    }
}