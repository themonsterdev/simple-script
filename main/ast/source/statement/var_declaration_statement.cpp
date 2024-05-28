/**
 * @file var_declaration_statement.cpp
 * @brief Implementation of the variable declaration statement class.
 */

// Include the declaration of the variable declaration statement class
#include "statement/var_declaration_statement.hpp"

// For std::invalid_argument
#include <stdexcept>

FVarDeclarationStatement::FVarDeclarationStatement(const std::string& identifier, ExpressionPtr expression)
	: m_identifier(identifier)
	// Move the expression into the member variable
	, m_expression(std::move(expression))
{
	if (m_identifier.empty())
	{
		throw std::invalid_argument("Identifier cannot be empty");
	}
}

std::string FVarDeclarationStatement::GetIdentifier() const
{
	// Return the identifier associated with this variable declaration
	return m_identifier;
}

const ExpressionPtr& FVarDeclarationStatement::GetExpression() const
{
	// Return the expression associated with this variable declaration
	return m_expression;
}

void FVarDeclarationStatement::Execute(const FContext& context) const
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
