/**
 * @file subtraction_expression.hpp
 * @brief Declaration of the FSubtractionExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for subtraction expressions.
 * This class represents subtraction expressions.
 */
class FSubtractionExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FSubtractionExpression object with the given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FSubtractionExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the subtraction expression.
     * @param context The evaluation context.
     * @return The value of the subtraction expression.
     */
    virtual ValuePtr Evaluate(const FContext& context) const override;
};
