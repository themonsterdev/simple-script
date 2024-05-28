#pragma once

#include "expression/abstract/compute_expression.hpp"

class FLogicalAndExpression final : public AComputeExpression
{
public:

    FLogicalAndExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
