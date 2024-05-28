/**
 * @file identifier_node.cpp
 * @brief Implementation of the identifier node class.
 */

// Include the header file for the FIdentifierNode class
#include "expression/identifier_node.hpp"

FIdentifierNode::FIdentifierNode(const std::string& name)
	// Initialize the name member with the provided name
	: m_name(name)
{}

const std::string& FIdentifierNode::GetName() const
{
	// Return the name of the identifier
	return m_name;
}

void FIdentifierNode::SetName(const std::string& name)
{
	// Set the name of the identifier to the provided name
	m_name = name;
}

Value FIdentifierNode::Evaluate(const FContext& context) const
{
	// Retrieve the value associated with the identifier from the context
	return context.GetVariable(m_name);
}
