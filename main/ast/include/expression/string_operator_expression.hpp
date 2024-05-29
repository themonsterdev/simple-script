/**
 * @file string_operator_expression.hpp
 * @brief Declaration of the string operator expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a string operator expression in the abstract syntax tree.
 *
 * This class inherits from the IExpression interface and represents a expression that
 * performs string operations, such as concatenation or repetition.
 */
class FStringOperatorExpression final : public IExpression
{
    std::string m_operator; // The string operator.
    ExpressionPtr m_left;   // The left operand.
    ExpressionPtr m_right;  // The right operand.

public:

    /**
     * @brief Constructs a string operator expression with the specified operator, left operand, and right operand.
     * @param op The string operator.
     * @param left The left operand.
     * @param right The right operand.
     */
    FStringOperatorExpression(const std::string& op, ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the string operation represented by this expression.
     * @param context The context in which the evaluation occurs.
     * @return The value resulting from the evaluation of the string operation.
     */
	virtual Value Evaluate(const FContext& context) const override;

    /**
     * @brief Returns the string operator.
     * @return The string operator.
     */
    std::string GetOperator() const;

    /**
     * @brief Returns the left operand of the string operator expression.
     * @return A constant reference to the left operand.
     */
    const ExpressionPtr& GetLeft() const;

    /**
     * @brief Returns the right operand of the string operator expression.
     * @return A constant reference to the right operand.
     */
    const ExpressionPtr& GetRight() const;
};
