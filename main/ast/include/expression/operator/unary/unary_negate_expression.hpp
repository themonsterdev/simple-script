/**
 * @file unary_negate_expression.hpp
 * @brief Declaration of the unary negate expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a unary negate expression.
 *
 * This class represents a unary negate expression that negates the value of its operand.
 */
class FUnaryNegateExpression final : public IExpression
{
public:

    /**
     * @brief Constructs a unary negate expression with the given operand.
     * @param expression The operand to be negated.
     */
    FUnaryNegateExpression(ExpressionPtr expression);

    /**
     * @brief Evaluates the unary negate expression based on the provided context.
     * @param context The context used for evaluation.
     * @return The result of the unary negate expression evaluation.
     */
    virtual ValuePtr Evaluate(const FContext& context) const override;

private:

    // The operand expression to be negated.
    ExpressionPtr m_expression;
};
