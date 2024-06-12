/**
 * @file not_equal_expression.hpp
 * @brief Declaration of the FNotEqualExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "ast/expression/abstract/compute_expression.hpp"

/**
 * @brief Class for not-equal expressions.
 * This class represents not-equal expressions.
 */
class FNotEqualExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FNotEqualExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FNotEqualExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the not-equal expression.
     * @param context The evaluation context.
     * @return The value of the not-equal expression.
     */
    ValuePtr Evaluate(const FContext& context) const override;
};
