/**
 * @file unary_not_expression.hpp
 * @brief Declaration of the unary not expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

/**
 * @brief Represents a unary not expression.
 *
 * This class represents a unary not expression that negates the boolean value of its operand.
 */
class FUnaryNotExpression final : public IExpression
{
public:

    /**
     * @brief Constructs a unary not expression with the given operand.
     * @param expression The operand to be negated.
     */
    FUnaryNotExpression(ExpressionPtr expression);

    /**
     * @brief Evaluates the unary not expression based on the provided context.
     * @param context The context used for evaluation.
     * @return The result of the unary not expression evaluation.
     */
    ValuePtr Evaluate(const FContext& context) const override;

private:

    // The operand expression to be negated.
    ExpressionPtr m_expression;
};
