#pragma once

#include "expression/abstract/compute_expression.hpp"

class FEqualToExpression final : public AComputeExpression
{
public:

    FEqualToExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
