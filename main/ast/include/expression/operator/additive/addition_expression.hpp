/**
 * @file addition_expression.hpp
 * @brief Declaration of the FAdditionExpression class.
 */
 
// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for addition expressions.
 * This class represents addition expressions.
 */
class FAdditionExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FAdditionExpression object with the given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FAdditionExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the addition expression.
     * @param context The evaluation context.
     * @return The value of the addition expression.
     */
    virtual Value Evaluate(const FContext& context) const override;
};
