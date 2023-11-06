#include <iostream>
#include <lox.hpp>

int main(int argc, char * argv[])
{
    Lox lox;
    if (argc > 2) {
        std::cout << "Usage: jlox [script]" << std::endl;
        exit(0);
    } else if (argc == 2) {
        lox.RunFile(argv[1]);
    } else {
        lox.RunPrompt();
    }
    return 0;
}