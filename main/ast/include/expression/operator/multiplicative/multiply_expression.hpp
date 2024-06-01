/**
 * @file multiply_expression.hpp
 * @brief Declaration of the FMultiplicationExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for multiplication expressions.
 * This class represents multiplication expressions.
 */
class FMultiplicationExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FMultiplicationExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FMultiplicationExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the multiplication expression.
     * @param context The evaluation context.
     * @return The value of the multiplication expression.
     */
    virtual Value Evaluate(const FContext& context) const override;
};
