#pragma once

#include "expression/abstract/compute_expression.hpp"

class FLogicalOrExpression final : public AComputeExpression
{
public:

    FLogicalOrExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
