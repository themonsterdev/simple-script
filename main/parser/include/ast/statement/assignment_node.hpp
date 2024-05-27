#pragma once

#include "ast/syntax_node.hpp"

/**
 * @brief Represents an assignment node in the syntax tree.
 *
 * This node contains an identifier and an expression. It assigns the result of
 * the expression to the identifier when evaluated.
 */
class FAssignmentNode final : public ASyntaxNode
{
	std::string m_identifier;	// The identifier to which the expression value will be assigned.
	ASyntaxNode* m_expression;	// The expression to be evaluated and assigned to the identifier.

public:

	/**
	 * @brief Constructs an FAssignmentNode with the given identifier and expression.
	 * @param identifier The identifier for the assignment.
	 * @param expression The expression to be evaluated and assigned.
	 */
	FAssignmentNode(const std::string& identifier, ASyntaxNode* expression);

	/**
	 * @brief Gets the type of this syntax node.
	 * @return The type of this syntax node.
	 */
	eSyntaxNodeType GetType() const override;

	/**
	 * @brief Gets the identifier of this assignment node.
	 * @return The identifier of this assignment node.
	 */
	std::string GetIdentifier() const;

	/**
	 * @brief Gets the expression of this assignment node.
	 * @return The expression of this assignment node.
	 */
	ASyntaxNode* GetExpression() const;

	/**
	 * @brief Evaluates this assignment node within the given context.
	 *
	 * This method evaluates the expression and assigns its value to the identifier in the context.
	 * @param context The context in which to evaluate the node.
	 * @return The result of the evaluation.
	 */
	virtual Value Evaluate(const FContext& context) const override;
};
