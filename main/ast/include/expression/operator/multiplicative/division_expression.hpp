/**
 * @file division_expression.hpp
 * @brief Declaration of the FDivisionExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for division expressions.
 * This class represents division expressions.
 */
class FDivisionExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FDivisionExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FDivisionExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the division expression.
     * @param context The evaluation context.
     * @return The value of the division expression.
     */
    virtual ValuePtr Evaluate(const FContext& context) const override;
};
