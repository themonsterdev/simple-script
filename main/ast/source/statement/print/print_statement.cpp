/**
 * @file print_statement.cpp
 * @brief Implementation of the print statement class.
 */

// Include the declaration of the FPrintStatement class
#include "statement/print/print_statement.hpp"

#include <iostream> // For standard input/output operations
#include <sstream>	// For string stream operations

/**
 * @brief Converts a Value variant to a string.
 * @param value The Value variant to convert.
 * @return The string representation of the value.
 */
static std::string ToString(const Value& value)
{
	std::stringstream ss;

	// Use std::visit to handle the different types of the variant
	std::visit([&](const auto& val) {
		// Convert the value to a string and append it to the stream
		ss << val;
		}, value);

	// Return the resulting string
	return ss.str();
}

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
	Value value = m_expression->Evaluate(context);

	// Print the string representation of the value
	std::cout << ToString(value) << std::endl;
}
