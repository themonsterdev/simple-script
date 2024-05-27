#include "ast/expression/number_node.hpp"

FNumberNode::FNumberNode(int value)
	: m_value(value)
{}

eSyntaxNodeType FNumberNode::GetType() const
{
	return eSyntaxNodeType::Number;
}

int FNumberNode::GetValue() const
{
	return m_value;
}

void FNumberNode::SetValue(int value)
{
	m_value = value;
}

Value FNumberNode::Evaluate(const FContext& context) const
{
	return m_value;
}
