/**
 * @file new_expression.cpp
 * @brief Implementation of the new expression class.
 */

// Include the header file for the FNewExpression class
#include "expression/memory/new_expression.hpp"

// Include declarations for context objects
#include "context.hpp"
#include <stdexcept>

FNewExpression::FNewExpression(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

ValuePtr FNewExpression::Evaluate(const FContext& context) const
{
    const auto& instance = m_expression->Evaluate(context);

    if (!instance)
    {
        throw std::runtime_error("Failed to evaluate new expression");
    }

    return instance;
}

const ExpressionPtr& FNewExpression::GetExpression() const
{
    return m_expression;
}
