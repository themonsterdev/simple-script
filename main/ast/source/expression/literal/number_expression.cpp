/**
 * @file number_expression.cpp
 * @brief Implementation of the number expression class.
 */

// Include the declaration of the number expression class
#include "expression/literal/number_expression.hpp"

FNumberExpression::FNumberExpression(int value)
	// Initialize the value member with the provided value
	: m_value(value)
{}

int FNumberExpression::GetValue() const
{
	// Return the integer value held by the expression
	return m_value;
}

void FNumberExpression::SetValue(int value)
{
	// Set the integer value held by the expression to the provided value
	m_value = value;
}

Value FNumberExpression::Evaluate(const FContext& context) const
{
	// Return the integer value held by the expression
	return m_value;
}
