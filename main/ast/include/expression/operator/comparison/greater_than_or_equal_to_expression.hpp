/**
 * @file greater_than_or_equal_to_expression.hpp
 * @brief Declaration of the FGreaterThanOrEqualToExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for greater-than-or-equal-to expressions.
 * This class represents greater-than-or-equal-to expressions.
 */
class FGreaterThanOrEqualToExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FGreaterThanOrEqualToExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FGreaterThanOrEqualToExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the greater-than-or-equal-to expression.
     * @param context The evaluation context.
     * @return The value of the greater-than-or-equal-to expression.
     */
    virtual Value Evaluate(const FContext& context) const override;
};
