#pragma once

#include "ast/expression/interface/expression.hpp"

class FNewInstanceStatement final : public IStatement
{
    ExpressionPtr m_expression;

public:

    FNewInstanceStatement(ExpressionPtr expression);

    void Execute(const FContext& context) const override;

    const ExpressionPtr& GetExpression() const;
};
