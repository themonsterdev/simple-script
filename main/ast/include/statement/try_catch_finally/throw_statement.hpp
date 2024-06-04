#pragma once

#include "statement/interface/statement.hpp"
#include "expression/interface/expression.hpp"

class FThrowStatement final : public IStatement
{
    ExpressionPtr m_expression;

public:

    FThrowStatement(ExpressionPtr expression);
    virtual void Execute(const FContext& context) const override;
};
