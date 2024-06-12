/**
 * @file equal_to_expression.hpp
 * @brief Declaration of the FEqualToExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "ast/expression/abstract/compute_expression.hpp"

/**
 * @brief Class for equal-to expressions.
 * This class represents equal-to expressions.
 */
class FEqualToExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FEqualToExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FEqualToExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the equal-to expression.
     * @param context The evaluation context.
     * @return The value of the equal-to expression.
     */
    ValuePtr Evaluate(const FContext& context) const override;
};
