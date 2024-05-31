/**
 * @file subtract_expression.hpp
 * @brief Declaration of the FSubtractExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for subtraction expressions.
 * This class represents subtraction expressions.
 */
class FSubtractExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FSubtractExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FSubtractExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the subtraction expression.
     * @param context The evaluation context.
     * @return The value of the subtraction expression.
     */
    virtual Value Evaluate(const FContext& context) const override;
};
