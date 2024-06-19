/**
 * @file var_declaration_statement.cpp
 * @brief Implementation of the variable declaration statement class.
 */

// Include the declaration of the variable declaration statement class
#include "ast/statement/declaration/var_declaration_statement.hpp"

// For std::invalid_argument
#include <stdexcept>

// Include declarations for context objects
#include "context/context.hpp"

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

void FVarDeclarationStatement::Execute(const FContext& context) const
{
	// Check if an expression is provided
	if (m_expression)
	{
		const auto& value = m_expression->Evaluate(context);

		// Evaluate the expression and assign its value to the variable in the context
		context.AddSymbol(m_identifier, value);
	}
	else // If no expression is provided, declare the variable in the context
	{
		context.DeclareSymbol(m_identifier);
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
