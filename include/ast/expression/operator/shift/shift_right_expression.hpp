/**
 * @file shift_right_expression.hpp
 * @brief Declaration of the FShiftRightExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "ast/expression/abstract/compute_expression.hpp"

/**
 * @brief Class for right shift expressions.
 * This class represents right shift expressions.
 */
class FShiftRightExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FShiftRightExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FShiftRightExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the right shift expression.
     * @param context The evaluation context.
     * @return The value of the right shift expression.
     */
    ValuePtr Evaluate(const FContext& context) const override;
};
