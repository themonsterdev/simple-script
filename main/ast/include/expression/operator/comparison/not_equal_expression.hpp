#pragma once

#include "expression/abstract/compute_expression.hpp"

class FNotEqualExpression final : public AComputeExpression
{
public:

    FNotEqualExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
