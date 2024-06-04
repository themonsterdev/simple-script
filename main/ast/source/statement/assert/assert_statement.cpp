/**
 * @file assert_statement.cpp
 * @brief Implementation of the assert statement class.
 */

 // Include the declaration of the assert statement class
#include "statement/assert/assert_statement.hpp"

// For runtime_error
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"
#include <cassert>

FAssertStatement::FAssertStatement(ExpressionPtr expression, std::string message)
// Initialize m_expression with the given expression and m_message with the given message
    : m_expression(std::move(expression)), m_message(std::move(message))
{}

void FAssertStatement::Execute(const FContext& context) const
{
    // Evaluate the expression
    Value value = m_expression->Evaluate(context);

    // Check if the expression evaluates to true
    if (value == Value(0) || value == Value(false) || value == Value(""))
    {
        // Throw an exception with the optional message if the assertion fails
        throw std::runtime_error(m_message.empty() ? "Assertion failed" : "Assertion failed: " + m_message);

        // assert(false, m_message.empty() ? "Assertion failed" : "Assertion failed: " + m_message);
    }
}
