#pragma once

#include "expression/interface/expression.hpp"

class FExpressionParser;

class IExpressionRule
{
public:

    virtual ~IExpressionRule() = default;

    virtual bool Match(FExpressionParser& parser) const = 0;

    virtual ExpressionPtr Parse(FExpressionParser& parser) const = 0;
};
