/**
 * @file arithmetic_operator_node.hpp
 * @brief Declaration of the arithmetic operator node class.
 */

#pragma once

 // Include the expression interface
#include "ast/expression/interface/expression.hpp"

 /**
  * @brief Represents an arithmetic operator node in the abstract syntax tree.
  *
  * This class inherits from the IExpression interface and represents a node
  * that performs arithmetic operations such as addition, subtraction,
  * multiplication, or division.
  */
class FArithmeticOperatorNode final : public IExpression
{
    std::string m_operator; // The arithmetic operator.
    ExpressionPtr m_left;   // The left operand.
    ExpressionPtr m_right;  // The right operand.

public:

    /**
     * @brief Constructs an arithmetic operator node with the specified operator, left operand, and right operand.
     * @param op The arithmetic operator.
     * @param left The left operand.
     * @param right The right operand.
     */
	FArithmeticOperatorNode(const std::string& op, ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Evaluates the arithmetic operation represented by this node.
     * @param context The context in which the evaluation occurs.
     * @return The value resulting from the evaluation of the arithmetic operation.
     */
	virtual Value Evaluate(const FContext& context) const override;

    /**
     * @brief Returns the arithmetic operator.
     * @return The arithmetic operator.
     */
    std::string GetOperator() const;

    /**
     * @brief Returns the left operand of the arithmetic operator.
     * @return A reference to the left operand.
     */
    const ExpressionPtr& GetLeft() const;

    /**
     * @brief Returns the right operand of the arithmetic operator.
     * @return A reference to the right operand.
     */
    const ExpressionPtr& GetRight() const;
};
