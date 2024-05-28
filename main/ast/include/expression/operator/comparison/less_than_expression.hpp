#pragma once

#include "expression/abstract/compute_expression.hpp"

class FLessThanExpression final : public AComputeExpression
{
public:

    FLessThanExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
