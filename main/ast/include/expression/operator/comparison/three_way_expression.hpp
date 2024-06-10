/**
 * @file three_way_expression.hpp
 * @brief Declaration of the three way expression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

class FThreeWayExpression final : public AComputeExpression
{
public:

    FThreeWayExpression(ExpressionPtr left, ExpressionPtr right);

    virtual ValuePtr Evaluate(const FContext& context) const override;
};
