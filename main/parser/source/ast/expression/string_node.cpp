#include "ast/expression/string_node.hpp"

FStringNode::FStringNode(const std::string& value)
	: m_value(value)
{}

eSyntaxNodeType FStringNode::GetType() const
{
	return eSyntaxNodeType::String;
}

std::string FStringNode::GetValue() const
{
	return m_value;
}

void FStringNode::SetValue(const std::string& value)
{
	m_value = value;
}

Value FStringNode::Evaluate(const FContext& context) const
{
	return m_value;
}
