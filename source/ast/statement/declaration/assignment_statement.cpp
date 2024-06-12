/**
 * @file assignment_statement.cpp
 * @brief Implementation of the assignment statement class.
 */

// Include the declaration of the assignment statement class
#include "ast/statement/declaration/assignment_statement.hpp"

// For runtime_error
#include <stdexcept>

// Include declarations for context objects
#include "context/context.hpp"

FAssignmentStatement::FAssignmentStatement(const std::string& identifier, ExpressionPtr expression)
    // Initialize m_identifier with the given identifier
    : m_identifier(identifier)
    // Initialize m_expression with the given expression
    , m_expression(std::move(expression))
{
    // Check if the expression pointer is null
    if (!m_expression)
    {
        throw std::runtime_error("Assignment expression is null");
    }
}

std::string FAssignmentStatement::GetIdentifier() const
{
    // Return the identifier (variable name) for this assignment
    return m_identifier;
}

const ExpressionPtr& FAssignmentStatement::GetExpression() const
{
    // Return a constant reference to the expression associated with this assignment
    return m_expression;
}

void FAssignmentStatement::Execute(const FContext& context) const
{
    // Check if the assignment expression is valid
    if (!m_expression)
    {
        throw std::runtime_error("Assignment expression is null");
    }

    // Assign the evaluated expression value to the variable in the context
    context.AssignVariable(m_identifier, m_expression->Evaluate(context));
}
