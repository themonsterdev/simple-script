#pragma once

#include <stdexcept>

// Interface pour les expressions
class IExpression
{
public:

    virtual int Interpret() = 0;
};

class FArithmeticExpression final : public IExpression
{
    char op;
    IExpression* left;
    IExpression* right;

public:

    FArithmeticExpression(char op, IExpression* left, IExpression* right)
        : op(op)
        , left(left)
        , right(right)
    {}

    int Interpret() override
    {
        int l = left->Interpret();
        int r = right->Interpret();

        switch (op)
        {
        case '+': return l + r;
        case '-': return l - r;
        case '*': return l * r;
        case '/': return l / r;
        case '%': return l % r;
        default: throw std::invalid_argument("Invalid operator");
        }
    }
};

class FNumberExpression final : public IExpression
{
    int value;

public:

    FNumberExpression(int value)
        : value(value)
    {}

    int Interpret() override
    {
        return value;
    }
};
