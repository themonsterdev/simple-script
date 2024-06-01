/**
 * @file bitwise_or_expression.hpp
 * @brief Declaration of the FBitwiseOrExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for bitwise OR expressions.
 * This class represents bitwise OR expressions.
 */
class FBitwiseOrExpression final : public AComputeExpression
{
public:
    /**
     * @brief Constructs an FBitwiseOrExpression object with the given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FBitwiseOrExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the bitwise OR expression.
     * @param context The evaluation context.
     * @return The value of the bitwise OR expression.
     */
    virtual Value Evaluate(const FContext& context) const override;
};
