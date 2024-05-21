#include "ast/statement/assignment_node.hpp"

AssignmentNode::AssignmentNode(const std::string& identifier, ASyntaxNode* expression)
	: m_identifier(identifier)
	, m_expression(expression)
{}

eSyntaxNodeType AssignmentNode::GetType() const
{
	return eSyntaxNodeType::AssignmentStatement;
}

std::string AssignmentNode::GetIdentifier() const
{
	return m_identifier;
}

ASyntaxNode* AssignmentNode::GetExpression() const
{
	return m_expression;
}
