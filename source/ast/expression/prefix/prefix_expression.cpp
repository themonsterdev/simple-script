/**
 * @file prefix_expression.cpp
 * @brief Implementation of the prefix expression class.
 */

// Include the header file for the FPrefixExpression class
#include "ast/expression/prefix/prefix_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

#include "ast/expression/identifier_expression.hpp"
#include "value/number_value.hpp"
#include <stdexcept>

FPrefixExpression::FPrefixExpression(ExpressionPtr expression, std::string op)
    : m_expression(std::move(expression))
    , m_op(op)
{}

ValuePtr FPrefixExpression::Evaluate(const FContext& context) const
{
    if (!m_expression)
    {
        throw std::runtime_error("m_expression is null");
    }

    const auto& identifier = dynamic_cast<FIdentifierExpression*>(m_expression.get());

    if (!identifier)
    {
        throw std::runtime_error("m_expression is not an identifier");
    }

    const auto& defaultValue = context.GetVariable(identifier->GetName());

    if (!defaultValue)
    {
        throw std::runtime_error("Variable not found in context");
    }
    
    if (!defaultValue->IsNumber())
    {
        throw std::runtime_error("Variable is not a number");
    }

    const auto& number = dynamic_cast<FNumberValue*>(defaultValue.get());

    auto value = number->GetValue();
    
    if (!number)
    {
        throw std::runtime_error("Value is not a FNumberValue");
    }

    if (m_op == "++")
    {
        ++value;
    }
    else if (m_op == "--")
    {
        --value;
    }
    else
    {
        throw std::runtime_error("Unsupported suffix operator: " + m_op);
    }

    number->SetValue(value);
    return defaultValue;
}
