/**
 * @file string_expression.cpp
 * @brief Implementation of the string expression class.
 */

 // Include the declaration of the string expression class
#include "ast/expression/literal/string_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

#include "value/string_value.hpp"

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

ValuePtr FStringExpression::Evaluate(const FContext& context) const
{
	// Evaluate to the string value
	return std::make_shared<FStringValue>(m_value);
}
