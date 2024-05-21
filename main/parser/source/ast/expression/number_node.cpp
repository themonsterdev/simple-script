#include "ast/expression/number_node.hpp"

NumberNode::NumberNode(int value)
	: m_value(value)
{}

eSyntaxNodeType NumberNode::GetType() const
{
	return eSyntaxNodeType::Number;
}

int NumberNode::GetValue() const
{
	return m_value;
}

void NumberNode::SetValue(int value)
{
	m_value = value;
}
