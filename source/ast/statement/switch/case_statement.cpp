/**
 * @file case_statement.cpp
 * @brief Implementation of the case statement class.
 */

// Include the header file for the case statement class
#include "ast/statement/switch/case_statement.hpp"

// Include declarations for context objects
#include "context/context.hpp"

// Constructor definition
FCaseStatement::FCaseStatement(ExpressionPtr condition, StatementPtr body)
    // Initialize m_condition with the given condition
    : m_condition(std::move(condition))
    // Initialize m_body with the given body
    , m_body(std::move(body))
{}

// Execute method definition
void FCaseStatement::Execute(const FContext& context) const
{
    // Execute the body of the case statement within the context
    if (m_body != nullptr)
    {
        m_body->Execute(context);
    }
}

// GetCondition method definition
const ExpressionPtr& FCaseStatement::GetCondition() const
{
    // Return a constant reference to the condition expression of this case statement
    return m_condition;
}

// GetBody method definition
const StatementPtr& FCaseStatement::GetBody() const
{
    // Return a constant reference to the body of statements associated with this case statement
    return m_body;
}
