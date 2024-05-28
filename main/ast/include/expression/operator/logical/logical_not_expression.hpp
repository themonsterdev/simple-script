#pragma once

#include "expression/interface/expression.hpp"

class FLogicalNotExpression final : public IExpression
{
    ExpressionPtr m_expression;

public:

    FLogicalNotExpression(ExpressionPtr expression);

    virtual Value Evaluate(const FContext& context) const override;

    const ExpressionPtr& GetExpression() const;
};
