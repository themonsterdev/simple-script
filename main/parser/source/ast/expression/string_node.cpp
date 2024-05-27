/**
 * @file string_node.cpp
 * @brief Implementation of the string node class.
 */

 // Include the declaration of the string node class
#include "ast/expression/string_node.hpp"

FStringNode::FStringNode(const std::string& value)
	// Initialize the string value
	: m_value(value)
{}

std::string FStringNode::GetValue() const
{
	// Return the string value
	return m_value;
}

void FStringNode::SetValue(const std::string& value)
{
	// Set the string value
	m_value = value;
}

Value FStringNode::Evaluate(const FContext& context) const
{
	// Evaluate to the string value
	return m_value;
}
