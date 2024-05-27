#include "ast/expression/identifier_node.hpp"

FIdentifierNode::FIdentifierNode(const std::string& name)
	: m_name(name)
{}

eSyntaxNodeType FIdentifierNode::GetType() const
{
	return eSyntaxNodeType::Identifier;
}

const std::string& FIdentifierNode::GetName() const
{
	return m_name;
}

void FIdentifierNode::SetName(const std::string& name)
{
	m_name = name;
}

Value FIdentifierNode::Evaluate(const FContext& context) const
{
	return context.GetVariable(m_name);
}
