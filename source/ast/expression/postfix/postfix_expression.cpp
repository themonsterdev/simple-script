/**
 * @file postfix_expression.cpp
 * @brief Implementation of the postfix expression class.
 */

// Include the header file for the FPostfixExpression class
#include "ast/expression/postfix/postfix_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

#include "ast/expression/identifier_expression.hpp"
#include "value/number_value.hpp"
#include <stdexcept>

FPostfixExpression::FPostfixExpression(ExpressionPtr expression, std::string op)
    : m_expression(std::move(expression))
    , m_op(op)
{}

ValuePtr FPostfixExpression::Evaluate(const FContext& context) const
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
    const auto& resultValue = std::make_shared<FNumberValue>(value);
    
    if (!number)
    {
        throw std::runtime_error("Value is not a FNumberValue");
    }

    if (m_op == "++")
    {
        value++;
    }
    else if (m_op == "--")
    {
        value--;
    }
    else
    {
        throw std::runtime_error("Unsupported postfix operator: " + m_op);
    }

    number->SetValue(value);
    return resultValue;
}
