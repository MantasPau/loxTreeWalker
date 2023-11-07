#pragma once

#include <token.hpp>

class ExprBase
{
public:
    
};

class Binary : ExprBase
{
    Binary(ExprBase _left, Token t, ExprBase _right) : left(_left), op(t), right(_right) {}
    ExprBase left;
    Token op;
    ExprBase right;
};

class Grouping : ExprBase
{
    Grouping(ExprBase _expression) : expression(_expression) {}
    ExprBase expression;
};

template <typename T>
class Literal : ExprBase
{
    Literal(T _value) : value(_value) {}
    T value;
};

class Unary : ExprBase
{
    Unary(Token t, ExprBase _right) : op(t), right(_right) {} 
    Token op;
    ExprBase right;
}