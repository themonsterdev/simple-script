/**
 * @file boolean_expression.cpp
 * @brief Implementation of the boolean expression class.
 */

// Include the declaration of the boolean expression class
#include "expression/literal/boolean_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

#include "boolean_value.hpp"

FBooleanExpression::FBooleanExpression(bool value)
	// Initialize the value member with the provided value
	: m_value(value)
{}

bool FBooleanExpression::GetValue() const
{
	// Return the boolean value held by the expression
	return m_value;
}

void FBooleanExpression::SetValue(bool value)
{
	// Set the boolean value held by the expression to the provided value
	m_value = value;
}

ValuePtr FBooleanExpression::Evaluate(const FContext& context) const
{
	// Return the boolean value held by the expression
	return std::make_shared<FBooleanValue>(m_value);
}
