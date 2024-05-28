#pragma once

#include "expression/abstract/compute_expression.hpp"

class FModuloExpression final : public AComputeExpression
{
public:

    FModuloExpression(ExpressionPtr left, ExpressionPtr right);

    virtual Value Evaluate(const FContext& context) const override;
};
