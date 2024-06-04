/**
 * @file call_statement.hpp
 * @brief Declaration of the call statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a call statement in the abstract syntax tree.
 *
 * This class inherits from IStatement and represents a statement that calls a function.
 */
class FCallStatement final : public IStatement
{
	// Pointer to the function call expression.
	ExpressionPtr m_functionCall;

public:

	/**
	 * @brief Constructs a call statement with the given function call expression.
	 * @param functionCall Pointer to the function call expression.
	 */
	FCallStatement(ExpressionPtr functionCall);

	/**
	 * @brief Gets the function call expression.
	 * @return Pointer to the function call expression.
	 */
	const ExpressionPtr& GetFunctionCall() const;

	/**
	 * @brief Executes the call statement.
	 * @param context The context in which the execution occurs.
	 * @return An empty value, as call statements do not produce a value.
	 */
	virtual void Execute(const FContext& context) const override;
};
