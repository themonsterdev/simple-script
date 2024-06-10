/**
 * @file expression_statement.cpp
 * @brief Implementation of the expression statement class.
 */

// Include the header file for the expression statement class
#include "statement/expression/expression_statement.hpp"

FExpressionStatement::FExpressionStatement(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

void FExpressionStatement::Execute(const FContext& context) const
{
    m_expression->Evaluate(context);
}

const ExpressionPtr& FExpressionStatement::GetExpression() const
{
    return m_expression;
}
