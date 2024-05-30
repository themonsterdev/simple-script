/**
 * @file const_declaration_statement.cpp
 * @brief Implementation of the const declaration statement class.
 */

// Include the declaration of the const declaration statement class
#include "statement/const_declaration_statement.hpp"

// For std::invalid_argument
#include <stdexcept>

FConstDeclarationStatement::FConstDeclarationStatement(const std::string& identifier, ExpressionPtr expression)
	: m_identifier(identifier)
	// Move the expression into the member const
	, m_expression(std::move(expression))
{
	if (m_identifier.empty())
	{
		throw std::invalid_argument("Identifier cannot be empty");
	}
}

std::string FConstDeclarationStatement::GetIdentifier() const
{
	// Return the identifier associated with this const declaration
	return m_identifier;
}

const ExpressionPtr& FConstDeclarationStatement::GetExpression() const
{
	// Return the expression associated with this const declaration
	return m_expression;
}

void FConstDeclarationStatement::Execute(const FContext& context) const
{
	// Check if an expression is provided
	if (m_expression)
	{
		// Evaluate the expression and assign its value to the const in the context
		auto value = m_expression->Evaluate(context);

		// Evaluate the expression and assign its value to the const in the context
		context.SetVariable(m_identifier, value);
	}
	else // If no expression is provided, throw an error
	{
		throw std::runtime_error("Constant declaration for '" + m_identifier + "' requires an initial value.");
	}
}
