/**
 * @file var_declaration_node.cpp
 * @brief Implementation of the variable declaration node class.
 */

// Include the declaration of the variable declaration node class
#include "ast/statement/var_declaration_node.hpp"

// For std::invalid_argument
#include <stdexcept>

FVarDeclarationNode::FVarDeclarationNode(const std::string& identifier, ExpressionPtr expression)
	: m_identifier(identifier)
	// Move the expression into the member variable
	, m_expression(std::move(expression))
{
	if (m_identifier.empty())
	{
		throw std::invalid_argument("Identifier cannot be empty");
	}
}

std::string FVarDeclarationNode::GetIdentifier() const
{
	// Return the identifier associated with this variable declaration
	return m_identifier;
}

const ExpressionPtr& FVarDeclarationNode::GetExpression() const
{
	// Return the expression associated with this variable declaration
	return m_expression;
}

void FVarDeclarationNode::Execute(const FContext& context) const
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
}
