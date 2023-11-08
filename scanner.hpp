#pragma once
#include <string>
#include <list>
#include <map>
#include <token.hpp>
#include <error.hpp>

class Scanner
{
public:
    Scanner(const std::string& _source) : source(_source) {
        FillKeywordsMap();
    }
    std::list<std::pair<void*, const std::type_info&> > * ScanTokens();

private:
    bool IsAtEnd() {
        return current >= (int)source.length();
    }
    bool IsDigit(char c) {
        return ((c >= '0') && (c <= '9'));
    }
    bool IsAlpha(char c) {
        return (((c >= 'a') && (c <= 'z')) ||
                ((c >= 'A') && (c <= 'Z')) ||
                 (c == '_'));
    }
    bool IsAlphaNumeric(char c) {
        return (IsAlpha(c) || IsDigit(c));
    }
    void Identifier();
    void ScanToken();
    void String();
    void Number();
    char Advance() {
        return source.at(current++);
    }
    bool Match(char expected) {
        if (IsAtEnd()) return false;
        if (source.at(current) != expected) return false;

        ++current;
        return true;
    }
    char Peek() {
        if (IsAtEnd()) return '\0';
        return source.at(current);
    }
    char PeekNext() {
        if (current + 1 >= (int)source.length()) return '\0';
        return source.at(current + 1);
    }
    void AddToken(TokenType type) {
        AddToken<std::string>(type, "NULL");
    }
    template <typename T>
    void AddToken(TokenType type, T literal) {
        std::string text = source.substr(start, current - start);
        //Token<T> t(type, text, literal, line);
        tokens.push_back(std::pair<void*, const std::type_info&> 
                        ((void*)(new Token<T>(type, text, literal, line)), typeid(T)));
    }
    void FillKeywordsMap();

    std::list<std::pair<void*, const std::type_info&> > tokens;
    int start = 0;
    int current = 0;
    int line = 0;
    const std::string source;
    Error err;
    std::map<std::string, TokenType> keywords;
};

void Scanner::FillKeywordsMap()
{
    keywords["and"] = AND;
    keywords["class"] = CLASS;
    keywords["else"] = ELSE;
    keywords["false"] = FALSE;
    keywords["for"] = FOR;
    keywords["fun"] = FUN;
    keywords["if"] = IF;
    keywords["nil"] = NIL;
    keywords["or"] = OR;
    keywords["print"] = PRINT;
    keywords["return"] = RETURN;
    keywords["super"] = SUPER;
    keywords["this"] = THIS;
    keywords["true"] = TRUE;
    keywords["var"] = VAR;
    keywords["while"] = WHILE;
}

void Scanner::Identifier()
{
    while (IsAlphaNumeric(Peek())) Advance();
    std::string text = source.substr(start, current - start);
    auto s = keywords.find(text);
    TokenType type;
    if (s != keywords.end())
        type = s->second;
    else type = IDENTIFIER;
    AddToken(type);
}

std::list<std::pair<void*, const std::type_info&> > * Scanner::ScanTokens()
{
    while (!IsAtEnd()) {
        start = current;
        ScanToken();
    }
    
    //Token<std::string> t(EOFT, "", "NULL", line);
    tokens.push_back(std::pair<void*, const std::type_info&> 
                    ((void*)(new Token<std::string>(EOFT, "", "NULL", line)), typeid(std::string)));
    return &tokens;
}

void Scanner::ScanToken()
{
    char c = Advance();
    switch (c)
    {
    case '(': AddToken(LEFT_PAREN); break;
    case ')': AddToken(RIGHT_PAREN); break;
    case '{': AddToken(LEFT_BRACE); break;
    case '}': AddToken(RIGHT_BRACE); break;
    case ',': AddToken(COMMA); break;
    case '.': AddToken(DOT); break;
    case '-': AddToken(MINUS); break;
    case '+': AddToken(PLUS); break;
    case ';': AddToken(SEMICOLON); break;
    case '*': AddToken(STAR); break;
    case '!': AddToken(Match('=') ? BANG_EQUAL : BANG); break;
    case '=': AddToken(Match('=') ? EQUAL_EQUAL : EQUAL); break;
    case '<': AddToken(Match('=') ? LESS_EQUAL : LESS); break;
    case '>': AddToken(Match('=') ? GREATER_EQUAL : GREATER); break;
    case '/':
        if (Match('/')) {
            //A comment goes until the end of the line.
            while ((Peek() != '\n') && (!IsAtEnd())) Advance();
        } else {
            AddToken(SLASH);
        }
        break;
    case ' ':
    case '\r':
    case '\t':
        //Ignore white spaces
        break;
    case '\n':
        line++;
        break;
    case '"': String(); break;
    default:
        if (IsDigit(c)) {
            Number();
        } else if (IsAlpha(c)) {
            Identifier();
        } else {
            err.Throw(line, "Unexpected character.");
        }
        break;
    }
}

void Scanner::String()
{
    while ((Peek() != '"') && !IsAtEnd()) {
        if (Peek() == '\n') line++;
        Advance();
    }

    if (IsAtEnd()) {
        err.Throw(line, "Unterminated string.");
        return;
    }

    Advance();
    std::string value = source.substr(start + 1, current - start - 2);
    AddToken<std::string>(STRING, value);
}

void Scanner::Number()
{
    while (IsDigit(Peek())) Advance();

    //Look for  a fractional part
    if ((Peek() == '.') && (IsDigit(PeekNext()))) {
        //Consume the "."
        Advance();
        while (IsDigit(Peek())) Advance();
    }
    AddToken<double>(NUMBER, atof(source.substr(start, current - start).c_str()));
}