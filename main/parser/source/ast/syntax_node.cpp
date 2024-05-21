#include "ast/syntax_node.hpp"

void ASyntaxNode::AddChild(ASyntaxNode* child)
{
	m_children.push_back(child);
}

const std::vector<ASyntaxNode*>& ASyntaxNode::GetChildren() const
{
	return m_children;
}

eSyntaxNodeType ASyntaxNode::GetType() const
{
	return eSyntaxNodeType::None;
}
