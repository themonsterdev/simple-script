#pragma once

#include "expression/abstract/compute_expression.hpp"

class FGreaterThanOrEqualToExpression final : public AComputeExpression
{
public:

    FGreaterThanOrEqualToExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
