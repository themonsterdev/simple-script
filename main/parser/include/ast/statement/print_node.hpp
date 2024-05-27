/**
 * @file print_node.hpp
 * @brief Declaration of the print statement node class.
 */

#pragma once

// Include the interface for language statements
#include "ast/statement/interface/statement.hpp"

// Include the interface for expressions
#include "ast/expression/interface/expression.hpp"

/**
 * @brief Represents a print statement node in the abstract syntax tree.
 *
 * This class inherits from IStatement and represents a node that prints the result
 * of evaluating an expression.
 */
class FPrintNode final : public IStatement
{
	// Pointer to the expression node to be printed.
	ExpressionPtr m_expression;

public:

	/**
	 * @brief Constructs a print statement node with the given expression.
	 * @param expression Pointer to the expression node to be printed.
	 */
	FPrintNode(ExpressionPtr expression);

	/**
	 * @brief Gets the expression node to be printed.
	 * @return Pointer to the expression node.
	 */
	const ExpressionPtr& GetExpression() const;

	/**
	 * @brief Evaluates the print statement node.
	 * @param context The context in which the evaluation occurs.
	 * @return An empty value, as print statements do not produce a value.
	 */
	virtual void Execute(const FContext& context) const override;
};
