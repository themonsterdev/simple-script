#include "ast/statement/print_statement_node.hpp"

PrintStatementNode::PrintStatementNode(ASyntaxNode* expression)
	: m_expression(expression)
{}

eSyntaxNodeType PrintStatementNode::GetType() const
{
	return eSyntaxNodeType::PrintStatement;
}

ASyntaxNode* PrintStatementNode::GetExpression() const
{
	return m_expression;
}
