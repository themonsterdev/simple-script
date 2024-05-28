#pragma once

#include "expression/abstract/compute_expression.hpp"

class FAdditionExpression final : public AComputeExpression
{
public:

    FAdditionExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
