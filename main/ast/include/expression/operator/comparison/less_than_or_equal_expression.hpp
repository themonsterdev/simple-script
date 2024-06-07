/**
 * @file less_than_or_equal_expression.hpp
 * @brief Declaration of the FLessThanOrEqualExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for less-than-or-equal expressions.
 * This class represents less-than-or-equal expressions.
 */
class FLessThanOrEqualExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FLessThanOrEqualExpression object with the given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FLessThanOrEqualExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the less-than-or-equal expression.
     * @param context The evaluation context.
     * @return The value of the less-than-or-equal expression.
     */
    virtual ValuePtr Evaluate(const FContext& context) const override;
};
