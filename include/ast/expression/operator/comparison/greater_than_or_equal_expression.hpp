/**
 * @file greater_than_or_equal_expression.hpp
 * @brief Declaration of the FGreaterThanOrEqualExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "ast/expression/abstract/compute_expression.hpp"

/**
 * @brief Class for greater-than-or-equal expressions.
 * This class represents greater-than-or-equal expressions.
 */
class FGreaterThanOrEqualExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FGreaterThanOrEqualExpression object with the given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FGreaterThanOrEqualExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the greater-than-or-equal expression.
     * @param context The evaluation context.
     * @return The value of the greater-than-or-equal expression.
     */
    ValuePtr Evaluate(const FContext& context) const override;
};
