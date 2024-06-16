/**
 * @file throw_expression.cpp
 * @brief Implementation of the throw expression class.
 */

// Include the header file for the FThrowExpression class
#include "ast/expression/exception/throw_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"
#include "value/string_value.hpp"

#include <stdexcept>
#include <iostream>

FThrowExpression::FThrowExpression(
    ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

ValuePtr FThrowExpression::Evaluate(const FContext& context) const
{
    if (!m_expression)
    {
        throw std::runtime_error("Unhandled exception occurred.");
    }

    ValuePtr value = m_expression->Evaluate(context);

    if (value->IsString())
    {
        const auto& result = std::dynamic_pointer_cast<FStringValue>(value);

        // throw std::exception(result->GetValue().c_str());

        // context.SetThrowFlag(true);
    }

    return value;
}
