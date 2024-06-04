/**
 * @file call_statement.cpp
 * @brief Implementation of the call statement class.
 */

// Include the declaration of the FCallStatement class
#include "statement/invokable/call_statement.hpp"

// Include declarations for context objects
#include "context.hpp"

#include <stdexcept>

FCallStatement::FCallStatement(ExpressionPtr functionCall)
	// Initialize m_functionCall with the given function call expression
	: m_functionCall(std::move(functionCall))
{
	// Check if the function call expression exists
	if (!m_functionCall)
	{
		throw std::runtime_error("Call statement has no function call expression to evaluate.");
	}
}

const ExpressionPtr& FCallStatement::GetFunctionCall() const
{
	// Return the function call expression associated with this call statement
	return m_functionCall;
}

void FCallStatement::Execute(const FContext& context) const
{
	// Evaluate the function call expression
	m_functionCall->Evaluate(context);
}
