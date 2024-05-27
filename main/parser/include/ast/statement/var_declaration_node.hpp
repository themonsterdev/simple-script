/**
 * @file var_declaration_node.hpp
 * @brief Declaration of the variable declaration node class.
 */

#pragma once

// Include the interface for language statements
#include "ast/statement/interface/statement.hpp"

// Include the interface for expressions
#include "ast/expression/interface/expression.hpp"

/**
 * @brief Represents a variable declaration node in the abstract syntax tree.
 *
 * This node contains an identifier and an optional expression.
 * When evaluated, it declares a variable with the given identifier and assigns the result of the expression to it if provided.
 */
class FVarDeclarationNode final : public IStatement
{
	// The identifier for the variable declaration.
	std::string m_identifier;

	// The optional expression to initialize the variable.
	ExpressionPtr m_expression;

public:

	/**
	 * @brief Constructs a variable declaration node with the given identifier and optional expression.
	 * @param identifier The identifier for the variable.
	 * @param expression The optional expression to initialize the variable.
	 */
	FVarDeclarationNode(const std::string& identifier, ExpressionPtr expression);

	/**
	 * @brief Returns the identifier of this variable declaration node.
	 * @return The identifier of this variable declaration node.
	 */
	std::string GetIdentifier() const;

	/**
	 * @brief Returns the expression associated with this variable declaration node.
	 * @return The expression associated with this variable declaration node.
	 */
	const ExpressionPtr& GetExpression() const;

	/**
	 * @brief Evaluates this variable declaration node within the given context.
	 *
	 * This method declares a variable with the specified identifier in the context
	 * and optionally assigns the result of the expression to it.
	 *
	 * @param context The context in which to evaluate the node.
	 */
	virtual void Execute(const FContext& context) const override;
};
