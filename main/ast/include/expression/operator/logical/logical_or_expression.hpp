/**
 * @file logical_or_expression.hpp
 * @brief Declaration of the FLogicalOrExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/abstract/compute_expression.hpp"

/**
 * @brief Class for logical OR expressions.
 * This class represents logical OR expressions.
 */
class FLogicalOrExpression final : public AComputeExpression
{
public:

    /**
     * @brief Constructs an FLogicalOrExpression object with given left and right operands.
     * @param left The left operand.
     * @param right The right operand.
     */
    FLogicalOrExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the logical OR expression.
     * @param context The evaluation context.
     * @return The value of the logical OR expression.
     */
    virtual ValuePtr Evaluate(const FContext& context) const override;
};
