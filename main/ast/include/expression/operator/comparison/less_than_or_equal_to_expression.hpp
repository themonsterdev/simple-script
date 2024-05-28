#pragma once

#include "expression/abstract/compute_expression.hpp"

class FLessThanOrEqualToExpression final : public AComputeExpression
{
public:

    FLessThanOrEqualToExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
