/**
 * @file bitwise_xor_expression.hpp
 * @brief Declaration of the FBitwiseXorExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for bitwise XOR expressions.
 * This class represents bitwise XOR expressions.
 */
class FBitwiseXorExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FBitwiseXorExpression object with the given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FBitwiseXorExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the bitwise XOR expression.
     * @param context The evaluation context.
     * @return The value of the bitwise XOR expression.
     */
    virtual Value Evaluate(const FContext& context) const override;
};
