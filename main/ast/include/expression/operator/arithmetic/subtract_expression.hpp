#pragma once

#include "expression/abstract/compute_expression.hpp"

class FSubtractExpression final : public AComputeExpression
{
public:

    FSubtractExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
