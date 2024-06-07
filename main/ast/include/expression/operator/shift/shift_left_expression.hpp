/**
 * @file shift_left_expression.hpp
 * @brief Declaration of the FShiftLeftExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for left shift expressions.
 * This class represents left shift expressions.
 */
class FShiftLeftExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FShiftLeftExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FShiftLeftExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the left shift expression.
     * @param context The evaluation context.
     * @return The value of the left shift expression.
     */
    virtual ValuePtr Evaluate(const FContext& context) const override;
};
