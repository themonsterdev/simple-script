/**
 * @file variable_declaration_statement.cpp
 * @brief Implementation of the variable declaration statement class.
 */

// Include the declaration of the variable declaration statement class
#include "ast/statement/variable/variable_declaration_statement.hpp"

// Include declarations for context objects
#include "context/context.hpp"

#include "value/number_value.hpp"

// For std::invalid_argument
#include <stdexcept>

FVariableDeclarationStatement::FVariableDeclarationStatement(
	const std::string& identifier,
	const std::string& type,
	ExpressionPtr initializer)
	: m_identifier(identifier)
	, m_type(type)
	, m_initializer(std::move(initializer))
{}

void FVariableDeclarationStatement::Execute(const FContext& context) const
{
	if (m_identifier.empty())
	{
		throw std::invalid_argument("Identifier cannot be empty");
	}

	// Check if an expression is provided
	if (m_initializer)
	{
		const auto& value = m_initializer->Evaluate(context);

		if (!m_type.empty())
		{
			if (m_type == "Number" && !value->IsNumber())
			{
				throw std::runtime_error("Type mismatch: expected 'Number' but got another type.");
			}
			else if (m_type == "String" && !value->IsString())
			{
				throw std::runtime_error("Type mismatch: expected 'String' but got another type.");
			}
			else if (m_type == "Boolean" && !value->IsBoolean())
			{
				throw std::runtime_error("Type mismatch: expected 'Boolean' but got another type.");
			}
			else if (m_type == "Function" && !value->IsFunction())
			{
				throw std::runtime_error("Type mismatch: expected 'Function' but got another type.");
			}
			else if (m_type == "Object" && !value->IsObject())
			{
				throw std::runtime_error("Type mismatch: expected 'Object' but got another type.");
			}
		}

		// Evaluate the expression and assign its value to the variable in the context
		context.SetVariable(m_identifier, value);
	}
	else // If no expression is provided, declare the variable in the context
	{
		context.DeclareVariable(m_identifier);
	}
}

std::string FVariableDeclarationStatement::GetIdentifier() const
{
	// Return the identifier associated with this variable declaration
	return m_identifier;
}

const ExpressionPtr& FVariableDeclarationStatement::GetExpression() const
{
	// Return the expression associated with this variable declaration
	return m_initializer;
}
