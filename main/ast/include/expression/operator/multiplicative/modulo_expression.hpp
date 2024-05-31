/**
 * @file modulo_expression.hpp
 * @brief Declaration of the FModuloExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for modulo expressions.
 * This class represents modulo expressions.
 */
class FModuloExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FModuloExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FModuloExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the modulo expression.
     * @param context The evaluation context.
     * @return The value of the modulo expression.
     */
    virtual Value Evaluate(const FContext& context) const override;
};
