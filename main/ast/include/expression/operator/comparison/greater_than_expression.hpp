/**
 * @file greater_than_expression.hpp
 * @brief Declaration of the FGreaterThanExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for greater-than expressions.
 * This class represents greater-than expressions.
 */
class FGreaterThanExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FGreaterThanExpression object with the given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FGreaterThanExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the greater-than expression.
     * @param context The evaluation context.
     * @return The value of the greater-than expression.
     */
    virtual ValuePtr Evaluate(const FContext& context) const override;
};
