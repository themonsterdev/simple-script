#include "ast/statement/var_declaration_node.hpp"

VarDeclarationNode::VarDeclarationNode(const std::string& identifier, ASyntaxNode* expression)
	: m_identifier(identifier)
	, m_expression(expression)
{}

eSyntaxNodeType VarDeclarationNode::GetType() const
{
	return eSyntaxNodeType::VariableDeclaration;
}

std::string VarDeclarationNode::GetIdentifier() const
{
	return m_identifier;
}

ASyntaxNode* VarDeclarationNode::GetExpression() const
{
	return m_expression;
}
