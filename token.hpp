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

class Token
{
public:
    Token();
    Token(const TokenType _type, const std::string _lexeme, const std::string _literal, const int line) : type(_type), lexeme(_lexeme), literalS(_literal), literalD(0), line(line) {literalType = LT_STRING;}
    Token(const TokenType _type, const std::string _lexeme, const double _literal, const int line) : type(_type), lexeme(_lexeme), literalS(""), literalD(_literal), line(line) {literalType = LT_DOUBLE;}
    std::string toString();
    friend std::ostream& operator<<(std::ostream& os, const Token& t);

private:
    TokenType type;
    std::string lexeme;
    std::string literalS;
    double literalD;
    LiteralType literalType;
    int line;
};

Token::Token()
{

}

std::ostream& operator<<(std::ostream& os, const Token& t)
{
    os << t.lexeme;
    return os;
}

std::string Token::toString()
{
    std::string str;
    switch (literalType)
    {
        case LT_STRING:
            str = literalS;
            break;
        case LT_DOUBLE:
            str = std::to_string(literalD);
            break;
    }
    return type + " " + lexeme + " " + str;
}