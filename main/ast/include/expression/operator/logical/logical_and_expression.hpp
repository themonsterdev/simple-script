/**
 * @file logical_and_expression.hpp
 * @brief Declaration of the FLogicalAndExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

 /**
  * @brief Class for logical AND expressions.
  * This class represents logical AND expressions.
  */
class FLogicalAndExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FLogicalAndExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FLogicalAndExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the logical AND expression.
     * @param context The evaluation context.
     * @return The value of the logical AND expression.
     */
    virtual Value Evaluate(const FContext& context) const override;
};
