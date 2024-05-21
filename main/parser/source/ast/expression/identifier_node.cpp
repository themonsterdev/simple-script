#include "ast/expression/identifier_node.hpp"

IdentifierNode::IdentifierNode(const std::string& name)
	: m_name(name)
{}

eSyntaxNodeType IdentifierNode::GetType() const
{
	return eSyntaxNodeType::Identifier;
}

const std::string& IdentifierNode::GetName() const
{
	return m_name;
}

void IdentifierNode::SetName(const std::string& name)
{
	m_name = name;
}
