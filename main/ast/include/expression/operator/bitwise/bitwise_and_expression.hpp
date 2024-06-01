/**
 * @file bitwise_and_expression.hpp
 * @brief Declaration of the FBitwiseAndExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for bitwise AND expressions.
 * This class represents bitwise AND expressions.
 */
class FBitwiseAndExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FBitwiseAndExpression object with the given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FBitwiseAndExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the bitwise AND expression.
     * @param context The evaluation context.
     * @return The value of the bitwise AND expression.
     */
    virtual Value Evaluate(const FContext& context) const override;
};
