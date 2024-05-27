#pragma once

#include "ast/syntax_node.hpp"

/**
 * @brief Represents a binary operator node in the abstract syntax tree.
 *
 * This class inherits from the ASyntaxNode class and represents a node that
 * performs binary operations, such as arithmetic or comparison operations.
 */
class ABinaryOperatorNode : public ASyntaxNode
{
protected:

	// The binary operator.
	std::string m_operator;

public:

	/**
	 * @brief Constructs a binary operator node with the specified operator, left operand, and right operand.
	 * @param op The binary operator.
	 * @param left The left operand.
	 * @param right The right operand.
	 */
	ABinaryOperatorNode(const std::string& op, ASyntaxNode* left, ASyntaxNode* right);

	/**
	 * @brief Returns the type of this node.
	 * @return The type of this node.
	 */
	eSyntaxNodeType GetType() const override;

	/**
	 * @brief Returns the binary operator.
	 * @return The binary operator.
	 */
	std::string GetOperator() const;

	/**
	 * @brief Returns the left operand of the binary operation.
	 * @return The left operand.
	 */
	const ASyntaxNode* GetLeft() const;

	/**
	 * @brief Returns the right operand of the binary operation.
	 * @return The right operand.
	 */
	const ASyntaxNode* GetRight() const;
};
