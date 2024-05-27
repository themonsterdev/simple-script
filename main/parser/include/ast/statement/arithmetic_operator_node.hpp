#pragma once

#include "ast/syntax_node.hpp"

/**
 * @brief Represents an arithmetic operator node in the abstract syntax tree.
 *
 * This class inherits from the ASyntaxNode class and represents a node
 * that performs arithmetic operations such as addition, subtraction, multiplication, or division.
 */
class FArithmeticOperatorNode final : public ASyntaxNode
{
    // The arithmetic operator.
    std::string m_operator;

public:

    /**
     * @brief Constructs an arithmetic operator node with the specified operator, left operand, and right operand.
     * @param op The arithmetic operator.
     * @param left The left operand.
     * @param right The right operand.
     */
	FArithmeticOperatorNode(const std::string& op, ASyntaxNode* left, ASyntaxNode* right);

    /**
     * @brief Returns the type of this node.
     * @return The type of this node.
     */
    eSyntaxNodeType GetType() const override;

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
};
