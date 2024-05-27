#include "ast/statement/var_declaration_node.hpp"

FVarDeclarationNode::FVarDeclarationNode(const std::string& identifier, ASyntaxNode* expression)
	: m_identifier(identifier)
	, m_expression(expression)
{
	if (m_identifier.empty())
	{
		throw std::invalid_argument("Identifier cannot be empty");
	}
}

eSyntaxNodeType FVarDeclarationNode::GetType() const
{
	// Return the type of this node as VariableDeclaration
	return eSyntaxNodeType::VariableDeclaration;
}

std::string FVarDeclarationNode::GetIdentifier() const
{
	// Return the identifier associated with this variable declaration
	return m_identifier;
}

ASyntaxNode* FVarDeclarationNode::GetExpression() const
{
	// Return the expression associated with this variable declaration
	return m_expression;
}

Value FVarDeclarationNode::Evaluate(const FContext& context) const
{
	// Check if an expression is provided
	if (m_expression)
	{
		// Evaluate the expression and assign its value to the variable in the context
		context.SetVariable(m_identifier, m_expression->Evaluate(context));
	}
	else // If no expression is provided, declare the variable in the context
	{
		context.DeclareVariable(m_identifier);
	}

	// Return an empty value
	return {};
}
