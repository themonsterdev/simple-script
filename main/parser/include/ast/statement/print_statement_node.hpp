#pragma once

#include "ast/syntax_node.hpp"

/**
 * @brief Represents a print statement node in the abstract syntax tree.
 *
 * This class inherits from ASyntaxNode and represents a node that prints the result
 * of evaluating an expression.
 */
class FPrintStatementNode final : public ASyntaxNode
{
	// Pointer to the expression node to be printed.
	ASyntaxNode* m_expression;

public:

	/**
	 * @brief Constructs a print statement node with the given expression.
	 * @param expression Pointer to the expression node to be printed.
	 */
	FPrintStatementNode(ASyntaxNode* expression);

	/**
	 * @brief Gets the type of the syntax node.
	 * @return The type of the syntax node.
	 */
	eSyntaxNodeType GetType() const override;

	/**
	 * @brief Gets the expression node to be printed.
	 * @return Pointer to the expression node.
	 */
	ASyntaxNode* GetExpression() const;

	/**
	 * @brief Evaluates the print statement node.
	 * @param context The context in which the evaluation occurs.
	 * @return An empty value, as print statements do not produce a value.
	 */
	virtual Value Evaluate(const FContext& context) const override;
};
