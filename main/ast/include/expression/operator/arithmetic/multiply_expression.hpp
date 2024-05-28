#pragma once

#include "expression/abstract/compute_expression.hpp"

class FMultiplyExpression final : public AComputeExpression
{
public:

    FMultiplyExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
