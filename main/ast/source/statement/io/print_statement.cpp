/**
 * @file print_statement.cpp
 * @brief Implementation of the print statement class.
 */

// Include the declaration of the FPrintStatement class
#include "statement/io/print_statement.hpp"

#include <iostream> // For standard input/output operations
#include <sstream>	// For string stream operations

// Include declarations for context objects
#include "context.hpp"

FPrintStatement::FPrintStatement(ExpressionPtr expression)
	// Initialize m_expression with the given expression
	: m_expression(std::move(expression))
{
	// Check if the expression exists
	if (!m_expression)
	{
		throw std::runtime_error("Print statement has no expression to evaluate.");
	}
}

const ExpressionPtr& FPrintStatement::GetExpression() const
{
	// Return the expression associated with this print statement
	return m_expression;
}

void FPrintStatement::Execute(const FContext& context) const
{
	// Evaluate the expression to be printed
	ValuePtr value = m_expression->Evaluate(context);

	// Print the string representation of the value
	std::cout << value->ToString() << std::endl;
}
