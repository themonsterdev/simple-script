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

#include "object_value.hpp"
#include "boolean_value.hpp"
#include "number_value.hpp"
#include "string_value.hpp"

FAssertStatement::FAssertStatement(ExpressionPtr expression, std::string message)
// Initialize m_expression with the given expression and m_message with the given message
    : m_expression(std::move(expression)), m_message(std::move(message))
{}

void FAssertStatement::Execute(const FContext& context) const
{
    // Evaluate the expression
    ValuePtr value = m_expression->Evaluate(context);

    bool condition = false;

    if (value->IsBoolean())
    {
        const auto& result = std::dynamic_pointer_cast<FBooleanValue>(value);
        condition = result->GetValue();

    }
    else if (value->IsNumber())
    {
        const auto& result = std::dynamic_pointer_cast<FNumberValue>(value);
        condition = result->GetValue() > 0;
    }
    else if (value->IsObject())
    {

    }
    else if (value->IsString())
    {
        const auto& result = std::dynamic_pointer_cast<FStringValue>(value);
        condition = result->GetValue().length() > 0;
    }

    // Check if the expression evaluates to true
    if (!condition)
    {
        // Throw an exception with the optional message if the assertion fails
        throw std::runtime_error(m_message.empty() ? "Assertion failed" : "Assertion failed: " + m_message);

        // assert(false, m_message.empty() ? "Assertion failed" : "Assertion failed: " + m_message);
    }
}
