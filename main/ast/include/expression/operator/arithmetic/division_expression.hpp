#pragma once

#include "expression/abstract/compute_expression.hpp"

class FDivisionExpression final : public AComputeExpression
{
public:

    FDivisionExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
