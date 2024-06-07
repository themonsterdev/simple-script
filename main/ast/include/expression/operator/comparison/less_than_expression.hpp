/**
 * @file less_than_expression.hpp
 * @brief Declaration of the FLessThanExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for less-than expressions.
 * This class represents less-than expressions.
 */
class FLessThanExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FLessThanExpression object with the given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FLessThanExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the less-than expression.
     * @param context The evaluation context.
     * @return The value of the less-than expression.
     */
    virtual ValuePtr Evaluate(const FContext& context) const override;
};
