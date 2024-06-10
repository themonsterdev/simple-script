/**
 * @file delete_expression.cpp
 * @brief Implementation of the delete expression class.
 */

// Include the header file for the FDeleteExpression class
#include "expression/memory/delete_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

FDeleteExpression::FDeleteExpression(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

ValuePtr FDeleteExpression::Evaluate(const FContext& context) const
{
    return {};
}

const ExpressionPtr& FDeleteExpression::GetExpression() const
{
    return m_expression;
}
