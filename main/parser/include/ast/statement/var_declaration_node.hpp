#pragma once

#include "ast/syntax_node.hpp"

/**
 * @brief Represents a variable declaration node in the abstract syntax tree.
 *
 * This node contains an identifier and an optional expression.
 * When evaluated, it declares a variable with the given identifier and assigns the result of the expression to it if provided.
 */
class FVarDeclarationNode final : public ASyntaxNode
{
	std::string m_identifier;	// The identifier for the variable declaration.
	ASyntaxNode* m_expression;	// The optional expression to initialize the variable.

public:

	/**
	 * @brief Constructs a variable declaration node with the given identifier and optional expression.
	 * @param identifier The identifier for the variable.
	 * @param expression The optional expression to initialize the variable.
	 */
	FVarDeclarationNode(const std::string& identifier, ASyntaxNode* expression);

	/**
	 * @brief Returns the type of this syntax node.
	 * @return The type of this syntax node.
	 */
	eSyntaxNodeType GetType() const override;

	/**
	 * @brief Returns the identifier of this variable declaration node.
	 * @return The identifier of this variable declaration node.
	 */
	std::string GetIdentifier() const;

	/**
	 * @brief Returns the expression associated with this variable declaration node.
	 * @return The expression associated with this variable declaration node.
	 */
	ASyntaxNode* GetExpression() const;

	/**
	 * @brief Evaluates this variable declaration node within the given context.
	 *
	 * This method declares a variable with the specified identifier in the context and optionally assigns the result of the expression to it.
	 * @param context The context in which to evaluate the node.
	 * @return The result of the evaluation.
	 */
	virtual Value Evaluate(const FContext& context) const override;
};
