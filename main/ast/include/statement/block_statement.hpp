/**
 * @file block_statement.hpp
 * @brief Declaration of the block statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

/**
 * @brief Represents an block statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * blocks the result of an expression to an identifier.
 */
class FBlockStatement final : public IStatement
{
	// The expression to be evaluated and assigned to the identifier.
	StatementList m_statements;

public:

	/**
	 * @brief Constructs an FBlockStatement with the given identifier and expression.
	 * @param identifier The identifier for the assignment.
	 * @param expression The expression to be evaluated and assigned.
	 */
	FBlockStatement(StatementList statements);

	/**
	 * @brief Gets the expression of this assignment node.
	 * @return The expression of this assignment node.
	 */
	const StatementList& GetStatements() const;

	/**
	 * @brief Executes this assignment node within the given context.
	 *
	 * This method evaluates the expression and assigns its value to the identifier in the context.
	 * @param context The context in which to evaluate the node.
	 */
	virtual void Execute(const FContext& context) const override;
};
