/**
 * @file number_node.cpp
 * @brief Implementation of the number node class.
 */

// Include the declaration of the number node class
#include "expression/number_node.hpp"

FNumberNode::FNumberNode(int value)
	// Initialize the value member with the provided value
	: m_value(value)
{}

int FNumberNode::GetValue() const
{
	// Return the integer value held by the node
	return m_value;
}

void FNumberNode::SetValue(int value)
{
	// Set the integer value held by the node to the provided value
	m_value = value;
}

Value FNumberNode::Evaluate(const FContext& context) const
{
	// Return the integer value held by the node
	return m_value;
}
