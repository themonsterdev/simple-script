/**
 * @file string_expression.cpp
 * @brief Implementation of the string expression class.
 */

 // Include the declaration of the string expression class
#include "expression/literal/string_expression.hpp"

FStringExpression::FStringExpression(const std::string& value)
	// Initialize the string value
	: m_value(value)
{}

std::string FStringExpression::GetValue() const
{
	// Return the string value
	return m_value;
}

void FStringExpression::SetValue(const std::string& value)
{
	// Set the string value
	m_value = value;
}

Value FStringExpression::Evaluate(const FContext& context) const
{
	// Evaluate to the string value
	return m_value;
}