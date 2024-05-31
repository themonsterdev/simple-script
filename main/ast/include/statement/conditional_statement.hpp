/**
 * @file conditional_statement.hpp
 * @brief Declaration of the conditional statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

class FConditionalStatement final : public IStatement
{
	ExpressionPtr m_condition;
	StatementPtr m_ifStatement;
	StatementList m_elseIfStatements;
	StatementPtr m_elseStatement;

public:

	FConditionalStatement(ExpressionPtr condition, StatementPtr ifStatement);

	/**
	 * @brief Executes this conditional statement within the given context.
	 *
	 * This method evaluates the expression and assigns its value to the identifier in the context.
	 * @param context The context in which to evaluate the node.
	 */
	virtual void Execute(const FContext& context) const override;

	bool EvaluateCondition(const FContext& context) const;

	void AddElseIfStatement(StatementPtr elseIfStatement);
	void SetElseStatement(StatementPtr elseStatement);

	const ExpressionPtr& GetCondition() const;
	const StatementPtr& GetIfStatement() const;
	const StatementList& GetElseIfStatements() const;
	const StatementPtr& GetElseStatement() const;
};
