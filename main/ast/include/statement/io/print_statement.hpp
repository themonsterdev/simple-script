/**
 * @file print_statement.hpp
 * @brief Declaration of the print statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a print statement in the abstract syntax tree.
 *
 * This class inherits from IStatement and represents a statement that prints the result
 * of evaluating an expression.
 */
class FPrintStatement final : public IStatement
{
	// Pointer to the expression to be printed.
	ExpressionPtr m_expression;

public:

	/**
	 * @brief Constructs a print statement with the given expression.
	 * @param expression Pointer to the expression to be printed.
	 */
	FPrintStatement(ExpressionPtr expression);

	/**
	 * @brief Gets the expression to be printed.
	 * @return Pointer to the expression.
	 */
	const ExpressionPtr& GetExpression() const;

	/**
	 * @brief Evaluates the print statement.
	 * @param context The context in which the evaluation occurs.
	 * @return An empty value, as print statements do not produce a value.
	 */
	virtual void Execute(const FContext& context) const override;
};
