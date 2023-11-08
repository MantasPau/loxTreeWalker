#pragma once
#include <iostream>
#include <string>

enum TokenType {
    //single-character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    //one or two character tokens
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    //literals
    IDENTIFIER, STRING, NUMBER,

    //Keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR, 
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    EOFT
};

enum LiteralType
{
    LT_STRING, LT_DOUBLE
};

template <typename T>
class Token
{
public:
//  Token();
    Token(const TokenType _type, const std::string _lexeme, const T _literal, const int line) : type(_type), lexeme(_lexeme), literal(_literal), line(line) {}
    std::string toString();
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Token<U>& t);
    
private:
    TokenType type;
    std::string lexeme;
    T literal;
    int line;
};

template <typename U>
std::ostream& operator<<(std::ostream& os, const Token<U>& t)
{
    os << t.lexeme;
    return os;
}

template <typename T>
std::string Token<T>::toString()
{
    std::string str;
    if (typeid(literal) == typeid(std::string))
        str = literal;
    else str = std::to_string(literal);
    return type + " " + lexeme + " " + str;
}