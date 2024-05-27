#include "ast/statement/print_statement_node.hpp"

#include <iostream>
#include <sstream>

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

FPrintStatementNode::FPrintStatementNode(ASyntaxNode* expression)
	// Initialize m_expression with the given expression
	: m_expression(expression)
{
	// Check if the expression exists
	if (!m_expression)
	{
		throw std::runtime_error("Print statement has no expression to evaluate.");
	}
}

eSyntaxNodeType FPrintStatementNode::GetType() const
{
	// Return the type of this node as PrintStatement
	return eSyntaxNodeType::PrintStatement;
}

ASyntaxNode* FPrintStatementNode::GetExpression() const
{
	// Return the expression associated with this print statement
	return m_expression;
}

Value FPrintStatementNode::Evaluate(const FContext& context) const
{
	// Evaluate the expression to be printed
	Value value = m_expression->Evaluate(context);

	// Print the string representation of the value
	std::cout << ToString(value) << std::endl;

	// Return an empty value, as print statements do not produce a value
	return {};
}
