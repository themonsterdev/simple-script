/**
 * @file default_statement.cpp
 * @brief Implementation of the default statement class.
 */

// Include the header file for the default statement class
#include "ast/statement/switch/default_statement.hpp"

// Include declarations for context objects
#include "context/context.hpp"

// Constructor definition
FDefaultStatement::FDefaultStatement(StatementPtr body)
    // Initialize m_body with the given body
    : m_body(std::move(body))
{}

// Execute method definition
void FDefaultStatement::Execute(const FContext& context) const
{
    // Execute the body of the default case statement within the context
    if (m_body != nullptr)
    {
        m_body->Execute(context);
    }
}

// GetBody method definition
const StatementPtr& FDefaultStatement::GetBody() const
{
    // Return a constant reference to the body of statements associated with this default statement
    return m_body;
}
