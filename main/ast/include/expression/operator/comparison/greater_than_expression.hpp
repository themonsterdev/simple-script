#pragma once

#include "expression/abstract/compute_expression.hpp"

class FGreaterThanExpression final : public AComputeExpression
{
public:

    FGreaterThanExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
