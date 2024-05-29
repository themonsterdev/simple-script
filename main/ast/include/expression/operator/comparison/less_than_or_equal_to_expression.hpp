/**
 * @file less_than_or_equal_to_expression.hpp
 * @brief Declaration of the FLessThanOrEqualToExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for less-than-or-equal-to expressions.
 * This class represents less-than-or-equal-to expressions.
 */
class FLessThanOrEqualToExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FLessThanOrEqualToExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FLessThanOrEqualToExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the less-than-or-equal-to expression.
     * @param context The evaluation context.
     * @return The value of the less-than-or-equal-to expression.
     */
    virtual Value Evaluate(const FContext& context) const override;
};
